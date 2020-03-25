#include "editor.h"
#include <iostream>

Editor::Editor(AlienEdit &parent, Vector2 position, Vector2 size, std::vector<std::string> &buffer): Component(parent, position, size), buf(buffer) {
	keypad(win, TRUE);
}

void Editor::refresh() {
	if (cursor.y < start.y) start.y = cursor.y;
	else if (cursor.y - start.y >= size.y - 1) start.y = cursor.y - (size.y - 1);

	size_t offset = tabOffset(buf[cursor.y], cursor.x);
	if (cursor.x + offset < start.x) start.x = cursor.x + offset;
	else if (cursor.x + offset - start.x >= size.x - 2) start.x = cursor.x + offset - (size.x - 2);

	werase(win);
	size_t lastLine = start.y + size.y;
	for (size_t i = start.y; i < buf.size() && i < lastLine; ++i) {
		std::string part = convertTabs(buf[i]);
		if (part.length() > start.x) mvwaddstr(win, i - start.y, 0, part.substr(start.x, size.x).c_str());
	}
}

void Editor::focus() {
	wmove(win, cursor.y - start.y, cursor.x + tabOffset(buf[cursor.y], cursor.x) - start.x);
}

int Editor::acceptInput(bool menuActive) {
	int ch = wgetch(win);
	if (menuActive || ch == KEY_RESIZE || ch == 27) return ch;

	switch(ch) {
		case 8: // Backspace
		case 127:
		case KEY_BACKSPACE:
			if (cursor.x <= 0 && cursor.y > 0) {
				size_t length = buf[--cursor.y].length();
				buf[cursor.y] += buf[cursor.y + 1];
				buf.erase(buf.begin() + cursor.y + 1);
				cursor.x = length;
			} else if (cursor.x > 0) {
				buf[cursor.y].erase(buf[cursor.y].begin() + --cursor.x);
			} else break;

			if (digitCount(buf.size()) != digitCount(buf.size() + 1)) ae.resizeWindows();
			ae.statusBar->unsavedChanges = true;
			break;
		case KEY_DC:
			if (cursor.x < buf[cursor.y].length()) {
				buf[cursor.y].erase(cursor.x, 1);
			} else if (cursor.y + 1 < buf.size()) {
				buf[cursor.y] += buf[cursor.y + 1];
				buf.erase(buf.begin() + cursor.y + 1);
			} else break;

			if (digitCount(buf.size()) != digitCount(buf.size() + 1)) ae.resizeWindows();
			ae.statusBar->unsavedChanges = true;
			break;
		case 10: // Enter
		case KEY_ENTER:
			buf.insert(buf.begin() + cursor.y + 1, buf[cursor.y].substr(cursor.x));
			buf[cursor.y].erase(cursor.x);
			++cursor.y;
			cursor.x = 0;

			if (digitCount(buf.size()) != digitCount(buf.size() - 1)) ae.resizeWindows();
			ae.statusBar->unsavedChanges = true;
			break;
		case KEY_UP:
			if (cursor.y <= 0) break;
			cursor.x = std::min(cursor.x, buf[--cursor.y].length());
			break;
		case KEY_DOWN:
			if (cursor.y >= buf.size() - 1) break;
			cursor.x = std::min(cursor.x, buf[++cursor.y].length());
			break;
		case KEY_LEFT:
			if (cursor.x <= 0) break;
			--cursor.x;
			break;
		case KEY_RIGHT:
			if (cursor.x >= buf[cursor.y].length()) break;
			++cursor.x;
			break;
		case '\t':
		case KEY_STAB:
			buf[cursor.y].insert(cursor.x, "\t"); // TODO make tabs or spaces configurable
			++cursor.x;
			ae.statusBar->unsavedChanges = true;
			break;
		default:
			std::string key = std::string(keyname(ch));
			if ((key.front() == '^' && key.length() > 1) || // Ignore Ctrl
					key.rfind("KE", 0) == 0) return OK; // Ignore other special keys (KEY_...)
			buf[cursor.y].insert(buf[cursor.y].begin() + cursor.x, ch);
			++cursor.x;
			ae.statusBar->unsavedChanges = true;
	}
	
	ae.queueRefresh(this);
	ae.queueRefresh(ae.statusBar.get());
	ae.queueRefresh(ae.lineNumbers.get());
	return OK;
}

Vector2 Editor::getStart() {
	return start;
}

Vector2 Editor::getCursor() {
	return cursor;
}
