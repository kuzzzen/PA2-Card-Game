#include "gameMenu.h"

GameMenu::GameMenu(const std::vector <std::shared_ptr<Card>> &cards)
        : Menu(cards), m_Hand(cards) {}


uint8_t GameMenu::showAndGetChoice(const std::string &title) {
    initialize(title, 30, 2);
    auto options = m_Options;
    options.emplace_back("Save and exit");
    options.emplace_back("Exit");
    auto listSize = m_Size + 2;
    int choice, hover = 0;
    if (!m_Hand.empty())
        showCard(m_Hand[0]);
    while (true) {
        for (uint8_t i = 0; i < (uint8_t) listSize; i++) {
            if (i == hover)
                wattron(m_Menu, A_REVERSE);
            mvwprintw(m_Menu, i + 1, 1, options[i].c_str());
            wattroff(m_Menu, A_REVERSE);
        }
        choice = wgetch(m_Menu);

        if (choice == KEY_UP) {
            hover -= 1;
            if (hover == -1)
                hover = 0;
            if (hover < (int) m_Hand.size())
                showCard(m_Hand[hover]);

        } else if (choice == KEY_DOWN) {
            hover += 1;
            if (hover == listSize)
                hover = listSize - 1;
            if (hover < (int) m_Hand.size())
                showCard(m_Hand[hover]);
        }
        if (choice == 10) {
            clear();
            endwin();
            return hover;
        }
    }
    getch();
    return 0;
}

void GameMenu::showCard(const std::shared_ptr <Card> &card) {
    uint8_t xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
//    xMax = std::max(xMax, 100);
//    yMax = std::max(xMax, 80);
    init_pair(1, COLOR_RED, COLOR_BLACK);

    auto cardFrame = newwin(yMax / 4, xMax / 10, yMax / 6, xMax / 2 - (xMax / 10) / 2);
    box(cardFrame, 0, 0);
    std::string title = card->getName() + " (" + card->getSuit() + ")";
    mvwprintw(cardFrame, 0, 0, title.c_str());
    mvwprintw(cardFrame, 2, 0, card->getDescription().c_str());
    wbkgd(cardFrame, COLOR_PAIR(1));
    wrefresh(cardFrame);
}