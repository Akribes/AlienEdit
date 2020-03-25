#include "statusbar.h"

StatusBar::StatusBar(AlienEdit &parent, Vector2 position, Vector2 size): Component(parent, position, size) {
	unsavedChanges = false;
	wbkgd(win, A_REVERSE);
}

void StatusBar::refresh() {
	werase(win);
	mvwaddstr(win, 0, 0, ae.getFile().c_str());
	if (unsavedChanges) waddch(win, '*');
	Vector2 cursor = ae.editor->getCursor();
	std::ostringstream pos;
	pos<<"("<<cursor.y + 1<<";"<<cursor.x + 1<<")"; // + 1: line numbers start at 1
	mvwaddstr(win, 0, size.x - pos.tellp(), pos.str().c_str());
	wrefresh(win);
}
