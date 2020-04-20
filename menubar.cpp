#include "menubar.h"

MenuBar::MenuBar(AlienEdit &parent, Vector2 position, Vector2 size): Component(parent, position, size) {
	selection = 0;
	active = false;

	mainMenu = {
		MenuItem("Save", [this]() { ae.writeFile(); }),
		MenuItem("Exit", [this]() { ae.stop(); }),
		MenuItem("Toggle selecting", [this]() { ae.editor->toggleSelect(); }),
		MenuItem("Copy", [this]() { ae.editor->copy(); }, [this]() { return ae.editor->isSelecting(); }),
		MenuItem("Cut", [this]() { ae.editor->cut(); }, [this]() { return ae.editor->isSelecting(); }),
		MenuItem("Paste", [this]() { ae.editor->paste(); }, [this]() { return ae.editor->hasClipboard(); })
	};
}

void MenuBar::refresh() {
	if (!mainMenu[selection].visible()) moveLeft(); // Prevent selection from being hidden

	werase(win);
	wmove(win, 0, 0);
	for (size_t i = 0; i < mainMenu.size(); ++i) {
		if (!mainMenu[i].visible()) continue;
		if (i != 0) waddch(win, ' ');
		if (active && selection == i) wattron(win, A_REVERSE);
		waddstr(win, mainMenu[i].name.c_str());
		wattroff(win, A_REVERSE);
	}
	wrefresh(win);
}

bool MenuBar::toggle() {
	active = !active;
	refresh();
	return active;
}

void MenuBar::moveLeft() {
	do selection = (selection - 1) % options();
	while (!mainMenu[selection].visible());
}

void MenuBar::moveRight() {
	do selection = (selection + 1) % options();
	while (!mainMenu[selection].visible());
}
void MenuBar::confirm() {
	mainMenu[selection].action();
	active = false;
	ae.queueRefresh(this);
}

size_t MenuBar::options() {
	return mainMenu.size();
}
