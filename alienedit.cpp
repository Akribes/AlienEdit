#include "alienedit.h"

AlienEdit::AlienEdit(const std::string &file): file(file) {
	running = false;

	// Ncurses stuff
	initscr();
	cbreak();
	noecho();
	nl();
	intrflush(stdscr, FALSE);
	set_escdelay(50);

	// Read into buffer
	readFile();

	// Create windows
	int height, width;
	getmaxyx(stdscr, height, width);
	size_t lineNumbersWidth = digitCount(buffer.size());

	editor = std::make_unique<Editor>(*this, Vector2(lineNumbersWidth + 1, 0), Vector2(width - lineNumbersWidth, height - 2), buffer);
	lineNumbers = std::make_unique<LineNumbers>(*this, Vector2(0, 0), Vector2(lineNumbersWidth, height - 2), buffer);
	menuBar = std::make_unique<MenuBar>(*this, Vector2(0, height - 2), Vector2(width, 1));
	statusBar = std::make_unique<StatusBar>(*this, Vector2(0, height - 1), Vector2(width, 1));
}

void AlienEdit::start() {
	running = true;

	refreshAll();
	while (running) {
		int ch = editor->acceptInput(menuBar->active);
		if (ch != OK) {
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
					menuBar->moveLeft();
					queueRefresh(menuBar.get());
					break;
				case KEY_RIGHT:
				case KEY_DOWN:
					menuBar->moveRight();
					queueRefresh(menuBar.get());
					break;
			}
		}
		refresh();
	}

	editor->destroy();
	menuBar->destroy();
	statusBar->destroy();
	lineNumbers->destroy();

	clear();
	refresh();
	endwin();
}

void AlienEdit::stop() {
	running = false;
}

void AlienEdit::resizeWindows() {
	int height, width;
	getmaxyx(stdscr, height, width);
	size_t lineNumbersWidth = digitCount(buffer.size());

	editor->resize(Vector2(lineNumbersWidth + 1, 0), Vector2(width - lineNumbersWidth - 1, height - 2));
	menuBar->resize(Vector2(0, height - 2), Vector2(width, 1));
	statusBar->resize(Vector2(0, height - 1), Vector2(width, 1));
	lineNumbers->resize(Vector2(0, 0), Vector2(lineNumbersWidth, height - 2));
	refreshAll();
}

void AlienEdit::queueRefresh(const Component *component) {
	refreshQueue.push_back(component);
}

void AlienEdit::refresh() {
	std::vector<const Component *> &q = refreshQueue;
	if (std::find(q.begin(), q.end(), statusBar.get()) != q.end()) statusBar->refresh();
	if (std::find(q.begin(), q.end(), menuBar.get()) != q.end()) menuBar->refresh();
	if (std::find(q.begin(), q.end(), editor.get()) != q.end()) editor->refresh();
	if (std::find(q.begin(), q.end(), lineNumbers.get()) != q.end()) lineNumbers->refresh();
	q.clear();
	editor->focus();
}

void AlienEdit::refreshAll() {
	statusBar->refresh();
	menuBar->refresh();
	editor->refresh();
	lineNumbers->refresh();
	refreshQueue.clear();
	editor->focus();
}

std::string AlienEdit::getFile() {
	return file;
}

void AlienEdit::readFile() {
	std::ifstream in;
	in.open(file);
	for (std::string line; std::getline(in, line); ) {
		buffer.push_back(line);
	}
	in.close();
	if (buffer.size() == 0) buffer.push_back("");
}

void AlienEdit::writeFile() {
	std::ofstream out;
	out.open(file);
	for (auto line : buffer) {
		out<<line<<'\n';
	}
	out.close();

	statusBar->unsavedChanges = false;
	queueRefresh(statusBar.get());
}
