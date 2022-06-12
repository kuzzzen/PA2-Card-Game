#ifndef GAME_H
#define GAME_H

#include <queue>
#include <memory>
#include "card.h"
#include "menus/menu.h"
#include "menus/gameMenu.h"
#include "players/player.h"
#include "players/playerComputer.h"


/// Largest class in program. Represents and handles games
class Game {
public:
    Game();

    Game(const std::queue <std::shared_ptr<Card>> &deck_, const int &gameMode);

    /// Additional constructor with HP for running games
    Game(const std::queue <std::shared_ptr<Card>> &deck_, const int &gameMode,
         const int &startHP1, const int &startHP2);

    ~Game() = default;

    /// Starts the game and fills players' hands with cards
    void start(const int &cardsPerHand1, const int &cardsPerHand2, bool loaded);

    /// Returns true if everyone is alive and has cards
    [[nodiscard]] bool isStillPlayable() const;

    /// Loads running game from file
    void loadFromFile(const std::string &gameName);

    /// Removes restricted suit from hand for one turn
    static std::vector <std::shared_ptr<Card>>
    removeRestricted(const std::vector <std::shared_ptr<Card>> &hand,
                     const std::string &suit);

    /// Helper function for one-liner text screens
    void showOneTextScreen(const std::string &text) const;


private:
    std::queue <std::shared_ptr<Card>> deck;    /// Shared deck of cards
    std::shared_ptr <Player> players[2]; // Players before they get assigned as "attack" and "defense"
    std::shared_ptr <Player> attack, defense;    /// Attack and defense. These values are swapped every turn
    static std::string getGameName();   /// To save game
    static void printHandIntoFile(std::ofstream &of, const std::vector <std::shared_ptr<Card>> &hand);

    void fillHand(std::vector <std::shared_ptr<Card>> &vector,
                  const int &count);  /// Fills hand with cards. Parameter "count" used to load running games with incomplete hands
    void showSwapScreen(const std::shared_ptr <Card> &lastCardPlayed, const std::string &hpOfNextAttacker,
                        const std::string &hpOfNextAttackersOpponent); /// Swap screen for PvP games
    void showGotCardScreen(const std::shared_ptr <Card> &card) const;   /// Screen showing new cards taken by player
    void showDrawScreen() const;    /// Screen players see when some game ends in a draw
    void showWinnerScreen(const std::string &winner) const;    /// Screen showing winner
    void saveGame();    /// Saves game to file
    void end(); /// clears players and ends game
    void handleGame(); /// Handles moves and game process in general
    void
    setNextToMove(const int &mode, const int &next);    /// Defines who is next to move when a running game is loaded
    void getGameSettings(std::ifstream &is, int &mode, int &hp1, int &hp2, int &cardsFirst, int &cardsSecond,
                         int &next) const; /// Analyses settings line for running games
    void getCardFromEffect(); /// Attacking player gets card that they should get because of their previous card's effect
    void showEndGameState() const;  /// Gets and displays result when the game is over

    uint8_t xMax{}, yMax{}; /// Borders of field defined by ncurses
};

#endif