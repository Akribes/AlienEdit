#include "linenumbers.h"

LineNumbers::LineNumbers(AlienEdit &parent, Vector2 position, Vector2 size, std::vector<std::string> &buffer): Component(parent, position, size), buf(buffer) {}

void LineNumbers::refresh() {
	start = ae.editor->getStart().y + 1;
	current = ae.editor->getCursor().y + 1;

	werase(win);
	for (size_t i = 0; i < size.y && i < buf.size(); ++i) {
		if (i + start == current) wattron(win, A_REVERSE);
		mvwaddstr(win, i, size.x - digitCount(i + start), std::to_string(i + start).c_str());
		wattroff(win, A_REVERSE);
	}
	wrefresh(win);
}
