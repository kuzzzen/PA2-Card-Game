#ifndef PLAYERCOMPUTER_H
#define PLAYERCOMPUTER_H

#include "player.h"

/// Represents computer with built-in card-picking algo
class PlayerComputer : public Player {
public:
    explicit PlayerComputer(const int &startHP);

    /// Makes computer choose best move to make; Returns -1 if all cards are blocked
    int pickBestMove();

private:
    uint8_t maxCardDamage;  /// Maximal damage effect computer has seen through the game
    int getBestCardOfSuit(std::string &suit);    /// Pics a card to get rid of some suit
    std::string suitToPlay;  ///  If the computer has too many cards of the same suit, it's better to throw them away to avoid lose by blocking
    int getDamage(const std::shared_ptr <Card> &card) const;    /// Gets damage value of some card
    int getHealing(const std::shared_ptr <Card> &card) const;   /// Gets healing value of some card
};

#endif
