#include <map>
#include <sstream>
#include "playerComputer.h"
#include "../game.h"

PlayerComputer::PlayerComputer(const int &startHP) : Player("computer", startHP), maxCardDamage(0) {}

int PlayerComputer::pickBestMove() {
    auto available = Game::removeRestricted(m_Hand, m_RestrictedSuit);
    if (available.empty()) {
        return -1;
    }
    // Search for card to win the game first, then proceed to analyze hand
    for (size_t i = 0; i < available.size(); i++) {
        auto card = available[i];
        for (const auto &effect: card->getEffects()) {
            if (effect->getIndex() == 0) // damage
                if (std::dynamic_pointer_cast<EffectDamage>(effect)->getValue() >= m_Opponent->getHp())
                    return i;
        }
    }
    int bestHealIndex = -1, bestHealValue = -1, bestDamageIndex = -1, bestDamageValue = -1;
    std::map<std::string, int> suitCountMap;
    for (int i = 0; i < (int) available.size(); i++) {
        auto damage = 0;
        auto healing = 0;
        if (damage > maxCardDamage) {
            maxCardDamage = damage;
        }
        if (damage > bestDamageValue) {
            bestDamageValue = damage;
            bestDamageIndex = i;
        }
        if (healing > bestHealValue) {
            bestHealValue = healing;
            bestHealIndex = i;
        }
        if (!suitCountMap.count(available[i]->getSuit())) {
            suitCountMap[available[i]->getSuit()] = 0;
        }
        suitCountMap[available[i]->getSuit()] += 1;
    }
    for (const auto &suit: suitCountMap) {
        if (suit.second > (int) (m_Hand.size() / 2)) {
            suitToPlay = suit.first;
        } else {
            suitToPlay = "";
        }
    }

    if (maxCardDamage >= m_Hp && bestHealIndex != -1) {
        return bestHealValue;
    } else if (!suitToPlay.empty()) {
        return getBestCardOfSuit(suitToPlay);
    } else if (bestDamageIndex != -1) {
        return bestDamageIndex;
    }
    return 0;
}

int PlayerComputer::getBestCardOfSuit(std::string &suit) {
    std::pair<int, int> bestCard;
    for (int i = 0; i < (int) m_Hand.size(); i++) {
        if (m_Hand[i]->getSuit() == suit) {
            auto damage = getDamage(m_Hand[i]);
            auto healing = getHealing(m_Hand[i]);
            if (damage + healing > bestCard.second) {
                bestCard = std::make_pair(i, damage + healing);
            }
        }
    }
    return bestCard.first;
}

int PlayerComputer::getHealing(const std::shared_ptr <Card> &card) const {
    std::string effect = card->getEffectsAsString();
    std::istringstream is(effect);
    int healing;
    is >> healing >> healing;
    return healing;
}

int PlayerComputer::getDamage(const std::shared_ptr <Card> &card) const {
    std::string effect = card->getEffectsAsString();
    std::istringstream is(effect);
    int damage;
    is >> damage;
    return damage;
}
