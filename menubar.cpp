#include "menubar.h"

MenuBar::MenuBar(AlienEdit &parent, Vector2 position, Vector2 size): Component(parent, position, size) {
	selection = 0;
	active = false;

	mainMenu = {
		std::make_pair("Save", [this]() { ae.writeFile(); }),
		std::make_pair("Exit", [this]() { ae.stop(); })
	};
}

void MenuBar::refresh() {
	werase(win);
	wmove(win, 0, 0);
	for (size_t i = 0; i < mainMenu.size(); ++i) {
		if (i != 0) waddch(win, ' ');
		if (active && selection == i) wattron(win, A_REVERSE);
		waddstr(win, mainMenu[i].first.c_str());
		wattroff(win, A_REVERSE);
	}
	wrefresh(win);
}

bool MenuBar::toggle() {
	active = !active;
	refresh();
	return active;
}

void MenuBar::confirm() {
	mainMenu[selection].second();
	active = false;
	ae.queueRefresh(this);
}

size_t MenuBar::options() {
	return mainMenu.size();
}
