#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

void initializeWindows();
void createWindows();
void handleResize();

void refreshStatus();
void refreshEditor(bool forceRedraw = false);

void readFromFile();
void writeToFile();

WINDOW *editor, *menu, *status;

std::string file;
std::vector<std::string> buffer;
int line, column, firstLine, firstColumn, lines, columns, height, width;

int main(int argc, char **argv) {
	line, column, firstLine, firstColumn = 0;

	if (argc > 1) {
		file = argv[1];
		readFromFile();
	}

	initializeWindows();
	
	if (buffer.size() == 0) buffer.push_back("");

	bool run = true;
	while (run) {
		int ch = wgetch(editor);
		switch(ch) {
			case KEY_RESIZE:
				handleResize();
				break;
			case KEY_DC: // TODO use something else to exit and make this remove the character after the cursor
				run = false;
				break;
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
				refreshEditor(true);
				refreshStatus();
				break;
			case 10: // Enter
				buffer.insert(buffer.begin() + line + 1, buffer[line].substr(column));
				buffer[line].erase(column);
				++line;
				column = 0;
				refreshEditor(true);
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
				refreshStatus();
		}
	}

	writeToFile(); // TODO add save feature and remove this

	clear();
	endwin();
	return 0;
}

void initializeWindows() {
	initscr();
	start_color();
	cbreak();
	noecho();
	clear();

	init_pair(1, COLOR_BLACK, COLOR_WHITE);

	createWindows();
}

void createWindows() {
	getmaxyx(stdscr, height, width);

	lines = height - 2;
	columns = width;

	editor = newwin(lines, width, 0, 0);
	refreshEditor();
	
	menu = newwin(1, width, height - 2, 0);
	waddstr(menu, "Eventually I will put a menu down here. For now, press Delete to exit. This is just a placeholder with some text so you can see that this exists.");
	wrefresh(menu);

	status = newwin(1, width, height - 1, 0);
	wbkgd(status, COLOR_PAIR(1));
	refreshStatus();
	
	keypad(editor, TRUE);
}

void handleResize() {
	delwin(editor);
	delwin(menu);
	createWindows();
}

void refreshStatus() {
	werase(status);
	mvwaddstr(status, 0, 0, file.c_str());
	std::ostringstream pos;
	pos<<"("<<line + 1<<";"<<column + 1<<")"; // + 1, because line numbers should start at 1
	mvwaddstr(status, 0, width - pos.tellp(), pos.str().c_str());
	wrefresh(status);
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
			if (part.length() > firstColumn) mvwaddstr(editor, i - firstLine, 0, part.substr(firstColumn, width).c_str());
		}
	}

	wmove(editor, line - firstLine, column - firstColumn);
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
}
