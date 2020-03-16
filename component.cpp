#include "component.h"
#include "alienedit.h"
Component::Component(Vector2 position, Vector2 size): pos(position), size(size) {
	win = newwin(size.y, size.x, pos.y, pos.x);
}

Component::~Component() {
	wclear(win);
	wrefresh(win);
	delwin(win);
}

void Component::resize(Vector2 newPosition, Vector2 newSize) {
	wclear(win);
	wrefresh(win);
	size = newSize;
	wresize(win, size.y, size.x);
	pos = newPosition;
	mvwin(win, pos.y, pos.x);
	wrefresh(win);
	refresh(true);
}
