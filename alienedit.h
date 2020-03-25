#ifndef ALIENEDIT_H
#define ALIENEDIT_H

#include "utils.h"
#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>
#include "component.h"
#include "editor.h"
#include "linenumbers.h"
#include "menubar.h"
#include "statusbar.h"

class AlienEdit {
	public:
		std::unique_ptr<Editor> editor;
		std::unique_ptr<MenuBar> menuBar;
		std::unique_ptr<LineNumbers> lineNumbers;
		std::unique_ptr<StatusBar> statusBar;

		explicit AlienEdit(const std::string &file);
		void start();
		void stop();

		void resizeWindows();
		void queueRefresh(const Component *component);
		void refresh();
		void refreshAll();

		std::string getFile();
		void readFile();
		void writeFile();

	private:
		bool running;
		const std::string &file;
		std::vector<std::string> buffer;
		std::vector<const Component *> refreshQueue;
};

#endif // ALIENEDIT_H
