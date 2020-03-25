#include "component.h"

Component::Component(AlienEdit &parent, Vector2 position, Vector2 size): ae(parent), pos(position), size(size) {
	win = newwin(size.y, size.x, pos.y, pos.x);
}

Component::~Component() {};

void Component::resize(Vector2 newPosition, Vector2 newSize) {
	wclear(win);
	wrefresh(win);
	size = newSize;
	wresize(win, size.y, size.x);
	pos = newPosition;
	mvwin(win, pos.y, pos.x);
	wrefresh(win);
}

void Component::destroy() {
	wclear(win);
	wrefresh(win);
	delwin(win);
}
