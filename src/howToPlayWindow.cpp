#include "howToPlayWindow.h"
#include <fstream>

void HowToPlayWindow::showHowTo(const std::string &path) {
    uint8_t xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    int ln = 1;
    std::string line;
    std::ifstream howToFile(path);
    while (std::getline(howToFile, line))
        mvaddstr(ln++, 5, line.c_str());
    auto menu = newwin(ln, xMax / 4, yMax - yMax / 2, xMax - 2 * xMax / 3);
    box(menu, 0, 0);
    refresh();
    keypad(menu, true);
    getch();
    clear();
    endwin();
}