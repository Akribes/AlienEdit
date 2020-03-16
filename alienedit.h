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

extern bool isRunning;

extern std::string file;

extern size_t height, width, lineNumbersWidth;

void initialise();
void createWindows();
void resizeWindows();

void refreshStatus();
void refreshLineNumbers();

void readFromFile();
void writeToFile();

extern Editor *editor;
extern MenuBar *menuBar;
extern LineNumbers *lineNumbers;
extern StatusBar *statusBar;

#endif // ALIENEDIT_H
