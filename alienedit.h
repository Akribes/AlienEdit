#ifndef ALIENEDIT_H
#define ALIENEDIT_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

extern bool isRunning;

extern std::string file;
extern std::vector<std::string> buffer;

extern WINDOW* editor, * lineNumbers, * menuBar, * statusBar;

extern std::vector<std::pair<std::string, void(*)()> > mainMenu;
extern bool menuActive;
extern int selection;

extern int height, width, lineNumbersWidth, line, column, lines, columns, firstLine, firstColumn;

void initialise();
void createWindows();
void recreateWindows();

void refreshStatus();
void refreshEditor(bool forceRedraw = false);
void refreshLineNumbers();
void refreshMenu();

void readFromFile();
void writeToFile();

int digitCount(int n);

void createMenu();

#endif // ALIENEDIT_H
