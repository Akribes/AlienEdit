#ifndef MENUBAR_H
#define MENUBAR_H

#include "component.h"
#include <ncurses.h>
#include <vector>
#include <utility>
#include <functional>

typedef struct MenuItem {
	std::string name;
	std::function<void ()> action;
	std::function<bool ()> visible;
	MenuItem(std::string name, std::function<void ()> action, std::function<bool ()> visible = []() { return true; }):
		name(name), action(action), visible(visible) {}
} MenuItem;

typedef std::vector<MenuItem> Menu;

class MenuBar: public Component {
	public:
		size_t selection;
		bool active;

		MenuBar(AlienEdit &parent, Vector2 position, Vector2 size);
		void refresh();
		bool toggle();
		void moveLeft();
		void moveRight();
		void confirm();
		size_t options();
	private:
		Menu mainMenu;
};

#include "alienedit.h"

#endif // MENUBAR_H
