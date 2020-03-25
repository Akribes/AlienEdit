#ifndef ALIENEDIT_H
#define ALIENEDIT_H

#include "utils.h"
#include "menubar.h"
#include "statusbar.h"
#include "editor.h"
#include "linenumbers.h"
#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

extern Editor *editor;
extern MenuBar *menuBar;
extern LineNumbers *lineNumbers;
extern StatusBar *statusBar;

extern bool isRunning;
extern std::string file;

void resizeWindows();

void readFromFile();
void writeToFile();

#endif // ALIENEDIT_H
