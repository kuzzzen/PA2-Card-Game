#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>

class Card;

#include "../card.h"


/// Represent a player. Extended with card-picking algorithm by PlayerComputer
class Player {
public:

    Player(const std::string &type_, const int &startHP);

    virtual ~Player() = default;

    /// True if HP > 0
    [[nodiscard]] bool isAlive() const;

    /// Makes move with a card and use its effects
    void makeMove(const std::shared_ptr <Card> &card);

    /// Gets HP
    [[nodiscard]] int getHp() const;

    /// Gets Type (human or computer)
    [[nodiscard]] std::string getType() const;

    /// Returns card a person should take because of effect
    [[nodiscard]] std::string getCardToTake() const;

    /// Returns restriction a person has because of effect
    [[nodiscard]] std::string getRestriction() const;

    /// Sets m_Opponent ton pointer to given player
    void setOpponent(const std::shared_ptr <Player> &player);

    /// Returns pointer to player's opponent
    std::shared_ptr <Player> getOpponent() const;

    /// Sets HP to some value
    void setHp(const int &newHp);

    /// Sets card a person should get because of effect
    void setCardToGet(const std::string &cardToGet);

    /// Sets restriction a person has because of effect
    void setRestrictedSuit(const std::string &restrictedSuit);

    friend class Game;


protected:
    int m_Hp;
    std::vector <std::shared_ptr<Card>> m_Hand;
    std::shared_ptr <Player> m_Opponent;
    std::string m_RestrictedSuit;
    std::string m_CardToGet;
    std::string m_Type;

    /// Removes played card from m_Hand
    void removeFromHand(const std::shared_ptr <Card> &card);
};

#endif