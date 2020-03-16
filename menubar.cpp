#include "menubar.h"
#include "alienedit.h"

MenuBar::MenuBar(Vector2 position, Vector2 size): Component(position, size) {
	selection = 0;
	active = false;

	mainMenu = {
		std::make_pair("Save", writeToFile),
		std::make_pair("Exit", [this]() { isRunning = false; })
	};
}

void MenuBar::refresh(bool force) {
	werase(win);
	wmove(win, 0, 0);
	for (size_t i = 0; i < mainMenu.size(); ++i) {
		if (i != 0) waddch(win, ' ');
		if (active && selection == i) wattron(win, A_REVERSE);
		waddstr(win, mainMenu[i].first.c_str());
		wattroff(win, A_REVERSE);
	}
	wrefresh(win);
	editor->refresh(); // move back cursor
}

bool MenuBar::toggle() {
	active = !active;
	refresh();
	return active;
}

void MenuBar::confirm() {
	mainMenu[selection].second();
	active = false;
	refresh();
}

size_t MenuBar::options() {
	return mainMenu.size();
}

/*
std::vector<std::pair<std::string, void(*)()> > mainMenu;
bool menuActive = false;
size_t selection = 0;

namespace menu {
	void save() {
		writeToFile();
	}

	void exit() {
		isRunning = false;
	}
}

void createMenu() {
	mainMenu.push_back(std::make_pair("Save", &menu::save));
	mainMenu.push_back(std::make_pair("Exit", &menu::exit));
}

void refreshMenu() {
	werase(menuBar);
	wmove(menuBar, 0, 0);
	for (size_t i = 0; i < mainMenu.size(); ++i) {
		if (i != 0) waddch(menuBar, ' ');
		if (menuActive && selection == i) wattron(menuBar, A_REVERSE);
		waddstr(menuBar, mainMenu[i].first.c_str());
		wattroff(menuBar, A_REVERSE);
	}
	wrefresh(menuBar);
	editor->focus();
}*/
