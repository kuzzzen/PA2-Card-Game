#include "game.h"
#include "deckLoader.h"
#include <fstream>
#include <sstream>

Game::Game() {
    getmaxyx(stdscr, yMax, xMax);
}

Game::Game(const std::queue <std::shared_ptr<Card>> &deck_, const int &gameMode) : deck(deck_) {
    players[1] = std::make_shared<Player>(Player("human", 100));
    if (gameMode == 0)
        players[0] = std::make_shared<PlayerComputer>(PlayerComputer(100));
    else
        players[0] = std::make_shared<Player>(Player("human", 100));
    getmaxyx(stdscr, yMax, xMax);
}

Game::Game(const std::queue <std::shared_ptr<Card>> &deck_, const int &gameMode, const int &startHP1,
           const int &startHP2) : deck(deck_) {
    players[1] = std::make_shared<Player>(Player("human", startHP1));
    if (gameMode == 0)
        players[0] = std::make_shared<PlayerComputer>(PlayerComputer(startHP2));
    else
        players[0] = std::make_shared<Player>(Player("human", startHP2));
    getmaxyx(stdscr, yMax, xMax);
}

void Game::start(const int &cardsPerHand1, const int &cardsPerHand2, bool loaded) {
    fillHand(players[0]->m_Hand, cardsPerHand1);
    fillHand(players[1]->m_Hand, cardsPerHand2);
    players[0]->setOpponent(players[1]);
    players[1]->setOpponent(players[0]);
    attack = players[0];
    defense = players[1];
    if (players[0]->getType() == players[1]->getType() && !loaded) {
        showOneTextScreen("The first to move will be named Player One, the second will be named Player Two!");
        showOneTextScreen("Player One, it's your turn. Press any button to start");
    }
    handleGame();
}

bool Game::isStillPlayable() const {
    return ((!deck.empty() || (!players[0]->m_Hand.empty() && !players[1]->m_Hand.empty()))
            && players[0]->isAlive() && players[1]->isAlive());
}

void Game::fillHand(std::vector <std::shared_ptr<Card>> &vector, const int &count) {
    while (vector.size() != (size_t) count && !deck.empty()) {
        vector.emplace_back(deck.front());
        deck.pop();
    }
}

void Game::showSwapScreen(const std::shared_ptr <Card> &lastCardPlayed, const std::string &hpOfNextAttacker,
                          const std::string &hpOfNextAttackersOpponent) {
    if (attack->getType() == defense->getType()) {
        mvaddstr(yMax - yMax / 2 - 2, xMax / 2 - 13, "Press any key to swap sides");
        getch();
        clear();
    }
    refresh();
    if (attack->getType() == defense->getType() || attack->getType() == "computer") {
        mvaddstr(5, xMax / 2 - 16, "Last card played by your opponent:");
        GameMenu::showCard(lastCardPlayed);
        mvaddstr(yMax - yMax / 2, xMax / 2 - hpOfNextAttacker.size() / 2, hpOfNextAttacker.c_str());
        mvaddstr(yMax - yMax / 2 + 1, xMax / 2 - hpOfNextAttackersOpponent.size() / 2,
                 hpOfNextAttackersOpponent.c_str());
        mvaddstr(yMax - yMax / 2 + 2, xMax / 2 - 13, "Press any key to continue");
        refresh();
        getch();
    }
    clear();
    endwin();
}

void Game::showGotCardScreen(const std::shared_ptr <Card> &card) const {
    mvaddstr(5, xMax / 2 - 14, "You have taken a new card:");
    refresh();
    GameMenu::showCard(card);
    mvaddstr(yMax - yMax / 2 + 2, xMax / 2 - 14, "Press any key to make a move");
    refresh();
    getch();
    clear();
    endwin();
}

void Game::showDrawScreen() const {
    showOneTextScreen("It's a draw! No more cards in the deck or someone's m_Hand is empty!");
}

void Game::showWinnerScreen(const std::string &winner) const {
    showOneTextScreen("Game over! The winner is " + winner);
}

void Game::loadFromFile(const std::string &gameName) {
    if (gameName == "You_have_no_saved_games") {
        showOneTextScreen("I SAID YOU HAVE NO SAVED GAMES!");
        return;
    }
    std::ifstream f("games/" + gameName);
    if (!f.good()) {
        throw std::invalid_argument("File the file is broken or does not exists.");
    }

    int mode, hp1, hp2, cardsFirst, cardsSecond, next;
    getGameSettings(f, mode, hp1, hp2, cardsFirst, cardsSecond, next);
    std::vector <std::shared_ptr<Card>> fileParsed = DeckLoader::load(f, true);
    std::queue <std::shared_ptr<Card>> parsedDeck;
    for (size_t i = fileParsed.size() - 1; i-- > 0;) {
        parsedDeck.push(fileParsed[i]);
    }

    *this = Game(parsedDeck, mode, hp1, hp2);
    setNextToMove(mode, next);
    this->start(cardsFirst, cardsSecond, true);

}

void Game::saveGame() {
    mvaddstr(5, xMax / 2 - 14, "Name this game: ");
    refresh();
    std::string gameName = getGameName();
    if (gameName.empty()) {
        gameName = "Enter a name next time!";
    }
    DeckLoader::insertUnderscores(gameName);

    std::ofstream of;
    if (of.bad()) {
        showOneTextScreen("Could not write game to file.");
        return;
    }
    of.open("games/" + gameName, std::ios::out);
    of << "- " << (attack == players[0] ? "1 " : "2 ")
       << (attack->getType() == defense->getType() ? 1 : 0)
       << " " << attack->getHp() << " " << defense->getHp()
       << " " << attack->m_Hand.size() << " " << defense->m_Hand.size() << std::endl;

    while (!deck.empty()) {
        of << deck.front()->getName() << " " << DeckLoader::insertUnderscores(deck.front()->getDescription())
           << " " << deck.front()->getSuit() << " " << deck.front()->getEffectsAsString()
           << std::endl;
        deck.pop();
    }
    printHandIntoFile(of, defense->m_Hand);
    printHandIntoFile(of, attack->m_Hand);

    std::string saved = "Game saved to games/" + gameName;
    mvaddstr(5, xMax / 2 - 14, saved.c_str());
    refresh();
    getch();
    clear();
    of.close();
}

void Game::printHandIntoFile(std::ofstream &of, const std::vector <std::shared_ptr<Card>> &hand) {
    for (const auto &card: hand)
        of << card->getName() << " " << DeckLoader::insertUnderscores(card->getDescription())
           << " " << card->getSuit() << " " << card->getEffectsAsString() << std::endl;
}

std::string Game::getGameName() {
    nocbreak();
    echo();
    std::string input;
    int ch = getch();
    while (ch != '\n') {
        input.push_back((char) ch);
        ch = getch();
    }
    return input;
}

void Game::getGameSettings(std::ifstream &is, int &mode, int &hp1, int &hp2, int &cardsFirst, int &cardsSecond,
                           int &next) const {
    std::string settingsLine;
    std::getline(is, settingsLine);
    std::stringstream hpStream(settingsLine);
    std::string miss;
    hpStream >> miss >> next >> mode >> hp1 >> hp2 >> cardsFirst >> cardsSecond;
    if (hpStream.fail() && !hpStream.eof()) {
        throw std::invalid_argument("Something went wrong when loading game data. Check input files. GAME");
    }
}

void Game::setNextToMove(const int &mode, const int &next) {
    std::string nextToMove = "Next to move is ";
    if (mode == 0) {
        std::swap(players[0], players[1]);
        nextToMove += "Human";
    } else {
        if (next == 1)
            nextToMove += "Player 1";
        else {
            nextToMove += "Player 2";
            std::swap(players[0], players[1]);
        }
    }
    showOneTextScreen(nextToMove);
}

std::vector <std::shared_ptr<Card>>
Game::removeRestricted(const std::vector <std::shared_ptr<Card>> &hand, const std::string &suit) {
    if (suit.empty()) return hand;
    std::vector <std::shared_ptr<Card>> tmp;
    for (const auto &card: hand) {
        if (card->getSuit() != suit)
            tmp.emplace_back(card);
    }
    return tmp;
}


void Game::handleGame() {
    int move;
    uint8_t moveCount = 0;
    while (isStillPlayable()) {
        if (moveCount++ > 1 && !deck.empty()) {
            attack->m_Hand.emplace_back(deck.front());
            if (attack->getType() == "human")
                showGotCardScreen(deck.front());
            deck.pop();
        }
        if (!attack->m_CardToGet.empty()) {
            getCardFromEffect();
            attack->m_CardToGet.clear();
        }
        auto handWithRestrictions = removeRestricted(attack->m_Hand, attack->m_RestrictedSuit);
        label:
        if (attack->getType() == "human") {
            if (handWithRestrictions.empty()) {
                showOneTextScreen("You lose! You ran out of cards to play with because your opponent blocked them!");
                attack->m_Hp = 0;
                break;
            }
            GameMenu playerMenu = GameMenu(handWithRestrictions);
            move = playerMenu.showAndGetChoice("Hand");
        } else {
            move = std::dynamic_pointer_cast<PlayerComputer>(attack)->pickBestMove();
            if (move == -1) {
                showOneTextScreen("You won! The computer ran out of cards to play with because you blocked them all!");
                attack->m_Hp = 0;
                break;
            }
        }

        // Check if exit chosen:
        if (move == (int) handWithRestrictions.size()) {
            saveGame();
            end();
            return;
        } else if (move == (int) handWithRestrictions.size() + 1) {
            Menu exitMenu = Menu({"Yes, exit", "Cancel"});
            uint8_t choice = exitMenu.showAndGetChoice("Are you sure? Everything unsaved will be lost.");
            if (choice == 0) {
                end();
                return;
            } else goto label;
        }

        auto lastPlayed = handWithRestrictions[move];
        attack->makeMove(handWithRestrictions[move]);
        std::string yourHpMessage = "Your HP: " + std::to_string(defense->m_Hp) + (defense->m_Hp > 0 ? "" : " (dead)");
        std::string oppHpMessage =
                "Opponent's HP: " + std::to_string(attack->m_Hp) + (attack->m_Hp > 0 ? "" : " (dead)");
        showSwapScreen(lastPlayed, yourHpMessage, oppHpMessage);
        attack->m_RestrictedSuit.clear();
        std::swap(attack, defense);
    }
    showEndGameState();
    end();
}

void Game::showEndGameState() const {
    if (deck.empty() && attack->isAlive() && defense->isAlive())
        showDrawScreen();
    else {
        std::string winner;
        if (players[0]->getType() != players[1]->getType())
            winner = (players[0]->getHp() > 0 ? players[0]->getType() : players[1]->getType());
        else
            winner = (players[0]->getHp() > 0 ? "Player One!" : "Player Two!");
        showWinnerScreen(winner);
    }
}

void Game::getCardFromEffect() {
    auto deckCopy = deck;
    bool got = false;
    while (!deckCopy.empty()) {
        if (deckCopy.front()->getName() == attack->m_CardToGet) {
            attack->m_Hand.emplace_back(deckCopy.front());
            showGotCardScreen(deckCopy.front());
            got = true;
            break;
        }
        deckCopy.pop();
    }
    if (!got && attack->getType() == "human")
        showOneTextScreen("Could not get card " + attack->m_CardToGet + " because there are no more left in the deck");
}

void Game::showOneTextScreen(const std::string &text) const {
    mvaddstr(5, xMax / 2 - text.size() / 2, text.c_str());
    refresh();
    getch();
    clear();
    endwin();
}

void Game::end() {
    players[0]->setOpponent(nullptr);
    players[1]->setOpponent(nullptr);
}