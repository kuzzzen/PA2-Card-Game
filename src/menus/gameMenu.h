#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "menu.h"

/// In-game menu with cards and save/exit options
class GameMenu : public Menu {
public:
    explicit GameMenu(const std::vector <std::shared_ptr<Card>> &cards);

    /// Show menu and return choice index but with cards (in-game hand menu)
    uint8_t showAndGetChoice(const std::string &title) override;

    /// Shows card
    static void showCard(const std::shared_ptr <Card> &card);

private:
    std::vector <std::shared_ptr<Card>> m_Hand; /// Player's cards
};

#endif
