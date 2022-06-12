#include "card.h"

Card::Card(std::string name, std::string description, std::string suit, std::vector <std::shared_ptr<Effect>> effects)
        : m_Title(std::move(name)), m_Description(std::move(description)), m_Suit(std::move(suit)),
          m_Effects(std::move(effects)) {}

std::vector <std::shared_ptr<Effect>> Card::getEffects() {
    return m_Effects;
}

std::string Card::getName() const {
    return m_Title;
}

std::string Card::getDescription() const {
    return m_Description;
}

std::string Card::getSuit() const {
    return m_Suit;
}

std::string Card::getEffectsAsString() const {
    std::string effectsList[4] = {"0", "0", "-", "-"}; // damage healing card restriction
    for (const auto &e: m_Effects)
        effectsList[e->getIndex()] = e->getStringRep();
    return effectsList[0] + " " + effectsList[1] + " " + effectsList[2] + " " + effectsList[3];
}