#include "alienedit.h"

Editor *editor;
MenuBar *menuBar;
LineNumbers *lineNumbers;
StatusBar *statusBar;

bool isRunning;

std::string file;
std::vector<std::string> buffer;
size_t height, width;

int main(int argc, char **argv) {
	if (argc > 1) {
		file = argv[1];
		readFromFile();
	}

	if (buffer.size() == 0) buffer.push_back("");
	
	initialise();

	isRunning = true;
	while (isRunning) {
		int ch = editor->acceptInput(menuBar->active);
		if (ch == OK) continue;

		switch(ch) {
			case KEY_RESIZE:
				resizeWindows();
				break;
			case 27: // Escape
				menuBar->toggle();
				break;
			case 10: // Enter
				menuBar->confirm();
				break;
			case KEY_LEFT:
			case KEY_UP:
				menuBar->selection = (menuBar->selection - 1) % menuBar->options();
				menuBar->refresh();
				break;
			case KEY_RIGHT:
			case KEY_DOWN:
				menuBar->selection = (menuBar->selection + 1) % menuBar->options();
				menuBar->refresh();
				break;
		}
	}

	delete editor;
	delete lineNumbers;
	delete menuBar;
	delete statusBar;
	clear();
	endwin();

	return 0;
}

void initialise() {
	initscr();
	cbreak();
	noecho();
	nl();
	intrflush(stdscr, FALSE);
	set_escdelay(50);
	clear();

	createWindows();
}

void createWindows() {
	getmaxyx(stdscr, height, width);

	size_t lineNumbersWidth = digitCount(buffer.size());
	size_t lines = height - 2;
	
	editor = new Editor(Vector2(lineNumbersWidth + 1, 0), Vector2(width - lineNumbersWidth, height - 2), &buffer);
	editor->refresh(true);

	lineNumbers = new LineNumbers(Vector2(0, 0), Vector2(lineNumbersWidth, lines), &buffer);
	lineNumbers->refresh();

	menuBar = new MenuBar(Vector2(0, height - 2), Vector2(width, 1));
	menuBar->refresh();

	statusBar = new StatusBar(Vector2(0, height - 1), Vector2(width, 1));
	statusBar->refresh();

	editor->refresh();
}

void resizeWindows() {
	getmaxyx(stdscr, height, width);
	size_t lineNumbersWidth = digitCount(buffer.size());

	editor->resize(Vector2(lineNumbersWidth + 1, 0), Vector2(width - lineNumbersWidth - 1, height - 2));
	menuBar->resize(Vector2(0, height - 2), Vector2(width, 1));
	statusBar->resize(Vector2(0, height - 1), Vector2(width, 1));
	lineNumbers->resize(Vector2(0, 0), Vector2(lineNumbersWidth, height - 2));
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
	
	statusBar->unsavedChanges = false;
	statusBar->refresh();
}
