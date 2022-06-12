#include <fstream>
#include <random>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include "deckLoader.h"

std::vector <std::shared_ptr<Card>> DeckLoader::load(std::ifstream &deckStream, bool noShuffle) {
    std::vector <std::shared_ptr<Card>> cardCollection;

    int cardDamage, cardHealing;
    std::string cardTitle, cardDescription, cardRestriction, cardGetCard, cardSuit;
    while (deckStream >> cardTitle >> cardDescription
                      >> cardSuit >> cardDamage >> cardHealing
                      >> cardGetCard >> cardRestriction) {
        if (cardTitle != "-") {
            std::vector <std::shared_ptr<Effect>> cardEffects;
            if (cardDamage > 0)
                cardEffects.emplace_back(EffectDamage(cardDamage).getPtr());
            if (cardHealing > 0)
                cardEffects.emplace_back(EffectHealing(cardHealing).getPtr());
            if (cardGetCard != "-")
                cardEffects.emplace_back(EffectGetCard(cardGetCard).getPtr());
            if (cardRestriction != "-")
                cardEffects.emplace_back(EffectRestriction(cardRestriction).getPtr());
            insertWhitespaces(cardDescription);
            cardCollection.emplace_back(std::make_shared<Card>(cardTitle, cardDescription, cardSuit, cardEffects));
        }
    }
    if (deckStream.fail() && !deckStream.eof()) {
        throw std::invalid_argument("Something went wrong when loading the deck. Check input files.");
    } else if (cardCollection.empty()) {
        throw std::invalid_argument("Could not start game because the deck is empty.");
    }
    if (!noShuffle) {
        auto randDev = std::random_device{};
        std::shuffle(cardCollection.begin(), cardCollection.end(), std::default_random_engine{randDev()});
    }
    return cardCollection;
}

std::queue <std::shared_ptr<Card>> DeckLoader::loadAsQueue(std::ifstream &deckStream, bool noShuffle) {
    std::queue <std::shared_ptr<Card>> deck;
    for (const auto &card: load(deckStream, noShuffle))
        deck.push(card);
    return deck;
}

void DeckLoader::insertWhitespaces(std::string &s) {
    for_each(s.begin(), s.end(), [](char &c) {
        if (c == '_')
            c = ' ';
    });
}

std::string DeckLoader::insertUnderscores(const std::string &s) {
    std::string tmp = s;
    for_each(tmp.begin(), tmp.end(), [](char &c) {
        if (c == ' ')
            c = '_';
    });
    return tmp;
}