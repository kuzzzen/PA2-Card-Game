#include "menu.h"
#include <iostream>

Menu::Menu(const std::initializer_list <std::string> &options) : m_Options{options} {
    m_Size = m_Options.size();
}

Menu::Menu(const std::vector <std::string> &options) : m_Options(options) {
    m_Size = m_Options.size();
}

Menu::Menu(const std::vector <std::shared_ptr<Card>> &options) {
    for (const auto &card: options) {
        m_Options.emplace_back(card->getName());
    }
    m_Size = m_Options.size();
}

void Menu::initialize(const std::string &title, const uint8_t &width, const int &extendBy) {
    initscr();
    start_color();
    noecho();
    cbreak();
    uint8_t xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    uint8_t realWidth = (width == 0 ? xMax / 4 : width);

    mvaddstr(yMax - yMax / 2 - 2, xMax / 2 - title.size() / 2, title.c_str());
    m_Menu = newwin(m_Size + 2 + extendBy, realWidth, yMax - yMax / 2, xMax / 2 - realWidth / 2);
    box(m_Menu, 0, 0);
    refresh();
    keypad(m_Menu, true);
}

uint8_t Menu::showAndGetChoice(const std::string &title) {
    initialize(title, 0, 0);
    int choice, hover = 0;
    while (true) {
        for (uint8_t i = 0; i < m_Size; i++) {
            if (i == hover)
                wattron(m_Menu, A_REVERSE);
            mvwprintw(m_Menu, i + 1, 1, m_Options[i].c_str());
            wattroff(m_Menu, A_REVERSE);
        }
        choice = wgetch(m_Menu);

        if (choice == KEY_UP) {
            hover -= 1;
            if (hover == -1)
                hover = 0;
        } else if (choice == KEY_DOWN) {
            hover += 1;
            if (hover == m_Size)
                hover = m_Size - 1;
        }
        if (choice == 10) {
            clear();
            endwin();
            return hover;
        }
    }

    getch();
}