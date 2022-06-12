#ifndef DECK_LOADER_H
#define DECK_LOADER_H

#include <queue>
#include <memory>
#include "card.h"

/// Class with static methods for loading decks. Also used in loading running games
class DeckLoader {
public:
    DeckLoader() = default;

    /// Returns deck from file as vector (for loading running games)
    static std::vector <std::shared_ptr<Card>> load(std::ifstream &deckPath, bool noShuffle);

    /// Returns deck from file as queue (for new games)
    static std::queue <std::shared_ptr<Card>> loadAsQueue(std::ifstream &deckPath, bool noShuffle);

    /// Changes underscores to whitespaces to get nicer card looks
    static void insertWhitespaces(std::string & s);

    /// Changes whitespaces back to underscores to save games
    static std::string insertUnderscores(const std::string &s);
};

#endif
