#include "alienedit.h"
#include "utils.h"

WINDOW *editor, *lineNumbers, *menuBar, *statusBar;

bool isRunning;

std::string file;
std::vector<std::string> buffer;
int line, column, firstLine, firstColumn, lines, columns, height, width, lineNumbersWidth;

bool unsavedChanges = false;

int main(int argc, char **argv) {
	line, column, firstLine, firstColumn = 0;

	if (argc > 1) {
		file = argv[1];
		readFromFile();
	}

	if (buffer.size() == 0) buffer.push_back("");
	
	initialise();

	isRunning = true;
	while (isRunning) {
		int ch = wgetch(editor);

		switch(ch) {
			case KEY_RESIZE:
				recreateWindows();
				break;
			case 27: // Escape
				menuActive = !menuActive;
				if (menuActive) selection = 0;
				refreshMenu();
				break;
		}

		if (menuActive) {
			switch(ch) {
				case 10: // Enter
					mainMenu[selection].second();
					menuActive = false;
					break;
				case KEY_LEFT:
				case KEY_UP:
					selection = (selection - 1) % mainMenu.size();
					break;
				case KEY_RIGHT:
				case KEY_DOWN:
					selection = (selection + 1) % mainMenu.size();
					break;
				default:
					continue;
			}
			refreshMenu();
			continue;
		}

		switch (ch) {
			case 8: // Backspace
			case 127:
			case 263:
				if (column <= 0 && line > 0) {
					int length = buffer[--line].length();
					buffer[line] += buffer[line + 1];
					buffer.erase(buffer.begin() + line + 1);
					column = length;
				} else if (column > 0) {
					buffer[line].erase(buffer[line].begin() + --column);
				} else break;
				
				if (digitCount(buffer.size()) != digitCount(buffer.size() + 1)) recreateWindows();
				
				refreshEditor(true);
				unsavedChanges = true;
				refreshStatus();
				break;
			case 10: // Enter
				buffer.insert(buffer.begin() + line + 1, buffer[line].substr(column));
				buffer[line].erase(column);
				++line;
				column = 0;

				if (digitCount(buffer.size()) != digitCount(buffer.size() - 1)) recreateWindows();

				refreshEditor(true);
				unsavedChanges = true;
				refreshStatus();
				break;
			case KEY_UP:
				if (line <= 0) break;
				column = std::min(column, static_cast<int>(buffer[--line].length()));
				refreshEditor();
				refreshStatus();
				break;
			case KEY_DOWN:
				if (line >= buffer.size() - 1) break;
				column = std::min(column, static_cast<int>(buffer[++line].length()));
				refreshEditor();
				refreshStatus();
				break;
			case KEY_LEFT:
				if (column <= 0) break;
				--column;
				refreshEditor();
				refreshStatus();
				break;
			case KEY_RIGHT:
				if (column >= buffer[line].length()) break;
				++column;
				refreshEditor();
				refreshStatus();
				break;
			default:
				std::string key = std::string(keyname(ch));
				if (key.front() == '^' && key.length() > 1 || key.rfind("KE", 0) == 0) break; // Ignore Ctrl or special keys that aren't handled

				++column;
				buffer[line].insert(buffer[line].begin() + column - 1, ch);

				refreshEditor(true); // Redraw, so ncurses doesn't overwrite other characters
				unsavedChanges = true;
				refreshStatus();
		}
	}

	clear();
	endwin();
	return 0;
}

void initialise() {
	createMenu();

	initscr();
	cbreak();
	noecho();
	set_escdelay(50);
	clear();

	createWindows();
}

void createWindows() {
	getmaxyx(stdscr, height, width);

	lineNumbersWidth = digitCount(buffer.size());
	lines = height - 2;
	columns = width - lineNumbersWidth - 1;
	
	lineNumbers = newwin(lines, lineNumbersWidth + 1, 0, 0);

	editor = newwin(lines, columns, 0, lineNumbersWidth + 1);
	refreshEditor(true);

	menuBar = newwin(1, width, height - 2, 0);
	refreshMenu();
	wrefresh(menuBar);

	statusBar = newwin(1, width, height - 1, 0);
	wbkgd(statusBar, A_REVERSE);
	refreshStatus();
	
	keypad(editor, TRUE);

	// Move cursor back to editor
	wmove(editor, line - firstLine, column - firstColumn);
}

void recreateWindows() {
	delwin(editor);
	delwin(lineNumbers);
	delwin(statusBar);
	delwin(menuBar);
	createWindows();
}

void refreshStatus() {
	werase(statusBar);
	mvwaddstr(statusBar, 0, 0, file.c_str());
	if (unsavedChanges) waddch(statusBar, '*');
	std::ostringstream pos;
	pos<<"("<<line + 1<<";"<<column + 1<<")"; // + 1, because line numbers should start at 1
	mvwaddstr(statusBar, 0, width - pos.tellp(), pos.str().c_str());
	wrefresh(statusBar);
}

void refreshEditor(bool forceRedraw) {
	bool redraw = false;
	if (line < firstLine) firstLine = line;
	else if (line - firstLine >= lines - 1) firstLine = line - (lines - 1);
	else redraw = true;

	if (column < firstColumn) firstColumn = column;
	else if (column - firstColumn >= columns - 1) firstColumn = column - (columns - 1);
	else redraw = true;

	if (redraw || forceRedraw) {
		werase(editor);
		int lastLine = firstLine + lines;
		for (int i = firstLine; i < buffer.size() && i < lastLine; ++i) {
			std::string &part = buffer[i];
			if (part.length() > firstColumn) mvwaddstr(editor, i - firstLine, 0, part.substr(firstColumn, columns).c_str());
		}
		refreshLineNumbers();
	}

	wmove(editor, line - firstLine, column - firstColumn);
}

void refreshLineNumbers() {
	werase(lineNumbers);
	for (int i = 0; i < lines && i < buffer.size(); ++i) {
		mvwaddstr(lineNumbers, i, lineNumbersWidth - digitCount(i + firstLine + 1), std::to_string(i + firstLine + 1).c_str());
	}
	wrefresh(lineNumbers);
}

void readFromFile() {
	std::ifstream in;
	in.open(file);
	for (std::string line; std::getline(in, line); ) {
		buffer.push_back(line);
	}
	in.close();
}

void writeToFile() {
	std::ofstream out;
	out.open(file);
	for (auto &line : buffer) {
		out<<line<<'\n';
	}
	out.close();
	
	unsavedChanges = false;
	refreshStatus();
}
