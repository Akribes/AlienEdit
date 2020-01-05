#include "alienedit.h"

std::vector<std::pair<std::string, void(*)()> > mainMenu;
bool menuActive = false;
int selection = 0;

namespace menu {
	void save() {
		writeToFile();
	}

	void exit() {
		werase(editor);
	}
}

void createMenu() {
	mainMenu.push_back(std::make_pair("Save", &menu::save));
	mainMenu.push_back(std::make_pair("Exit", &menu::exit));
}

void refreshMenu() {
	selection = 0;
	werase(menuBar);
	wmove(menuBar, 0, 0);
	for (int i = 0; i < mainMenu.size(); ++i) {
		if (i != 0) waddch(menuBar, ' ');
		if (!menuActive || i != selection) wattron(menuBar, COLOR_PAIR(1));
		waddstr(menuBar, mainMenu[i].first.c_str());
		wattroff(menuBar, COLOR_PAIR(1));
	}
}
