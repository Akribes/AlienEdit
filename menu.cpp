#include "alienedit.h"

std::vector<std::pair<std::string, void(*)()> > mainMenu;
bool menuActive = false;
int selection = 0;

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
	for (int i = 0; i < mainMenu.size(); ++i) {
		if (i != 0) waddch(menuBar, ' ');
		if (menuActive && selection == i) wattron(menuBar, A_REVERSE);
		waddstr(menuBar, mainMenu[i].first.c_str());
		wattroff(menuBar, A_REVERSE);
	}
	wrefresh(menuBar);
	wrefresh(editor); // Move back cursor
}
