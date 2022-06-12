#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <memory>
#include "effects/effect.h"
#include "effects/effectDamage.h"
#include "effects/effectHealing.h"
#include "effects/effectGetCard.h"
#include "effects/effectRestriction.h"

/// A class representing card structure
class Card {
public:

    Card(std::string name, std::string description, std::string suit, std::vector <std::shared_ptr<Effect>> effects);

    virtual ~Card() = default;

    /// Returns vector of some card's effects
    std::vector <std::shared_ptr<Effect>> getEffects();

    /// Returns card name
    [[nodiscard]] std::string getName() const;

    /// Returns card description
    [[nodiscard]] std::string getDescription() const;

    /// Returns effect list as a string. Used for saving games into files
    [[nodiscard]] std::string getEffectsAsString() const;

    /// Returns suit
    [[nodiscard]] std::string getSuit() const;

protected:
    std::string m_Title, m_Description, m_Suit;
    std::vector <std::shared_ptr<Effect>> m_Effects;    /// Collection of effect a card has
};

#endif
