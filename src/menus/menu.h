#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <string>
#include <vector>
#include "../card.h"

/// Class menu used as main menu and base class for in-game menu
class Menu {
public:
    Menu(const std::initializer_list <std::string> &options);

    explicit Menu(const std::vector <std::shared_ptr<Card>> &options);

    explicit Menu(const std::vector <std::string> &options);

    virtual ~Menu() = default;

    /// Show menu and return choice index
    virtual uint8_t showAndGetChoice(const std::string &title);

protected:
    /// Initializes a menu
    virtual void initialize(const std::string &title, const uint8_t &width, const int &extendBy);

    std::vector <std::string> m_Options;    /// Menu options
    uint8_t m_Size;
    WINDOW *m_Menu{};   /// ncurses window
};

#endif