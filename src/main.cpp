#include <iostream>
#include <fstream>
#include "menus/menu.h"
#include "game.h"
#include "howToPlayWindow.h"
#include "deckLoader.h"
#include <filesystem>
#include <fstream>

#define DECKS_PATH "decks"
#define GAMES_PATH "games"
#define HOW_TO_PATH "resources/how_to_play"


/// Loading files via filesystem
std::vector <std::string> getFiles(const std::string &dir, const int &index) {
    std::vector <std::string> files;
    for (const auto &entry: std::filesystem::directory_iterator(dir)) {
        std::string filePath = entry.path();
        std::string name = filePath.substr(index);
        if (name[0] != '.')
            files.emplace_back(name);
    }
    if (files.empty()) files.emplace_back("You_have_no_saved_games");
    return files;
}

/// Loading and starting running game
void loadAndStart(const std::string &path) {
    auto games = getFiles(path, 6);
    Menu gameMenu = Menu(games);
    uint8_t gameOptions = gameMenu.showAndGetChoice("Choose game to load");
    Game game;
    try {
        game.loadFromFile(games[gameOptions]);
    } catch (std::invalid_argument &ia) {
        game.showOneTextScreen(ia.what());
    }
}

/// Starting a new game with a chosen deck
void pickDeckAndStart(const std::string &path, const int &option) {
    auto decks = getFiles(path, 6);
    Menu deckMenu = Menu(decks);
    uint8_t deckOption = deckMenu.showAndGetChoice("Choose deck");
    std::ifstream f("decks/" + decks[deckOption]);
    try {
        auto chosenDeck = DeckLoader::loadAsQueue(f, false);
        Game game = Game(chosenDeck, option);
        game.start(5, 5, false);
    } catch (std::invalid_argument &ia) {
        Game game;
        game.showOneTextScreen(ia.what());
    }
}


/// Waits for user's choice in main menu and handles it
int main() {
    while (true) {
        Menu mainMenu = Menu({"Against computer", "Against friend", "Load game", "How to play", "Exit"});
        uint8_t option = mainMenu.showAndGetChoice("Main Menu");
        if (option == 0 || option == 1) {
            pickDeckAndStart(DECKS_PATH, option);
        } else if (option == 2) {
            loadAndStart(GAMES_PATH);
        } else if (option == 3) {
            HowToPlayWindow::showHowTo(HOW_TO_PATH);
        } else break;
    }
    return 0;
}