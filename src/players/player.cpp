#include "player.h"

Player::Player(const std::string &type_, const int &startHP) : m_Hp(startHP), m_Type(type_) {}

void Player::makeMove(const std::shared_ptr <Card> &card) {
    for (const auto &effect: card->getEffects()) {
        effect->onPlayedBy(std::make_shared<Player>(*this));
    }
    removeFromHand(card);
}

void Player::removeFromHand(const std::shared_ptr <Card> &card) {
    for (auto it = m_Hand.begin(); it != m_Hand.end(); ++it) {
        if ((*it)->getName() == card->getName()) {
            m_Hand.erase(it);
            break;
        }
    }
}

/* Getters and setter: */
std::string Player::getCardToTake() const {
    return m_CardToGet;
}

std::string Player::getRestriction() const {
    return m_RestrictedSuit;
}

bool Player::isAlive() const {
    return m_Hp > 0;
}

int Player::getHp() const {
    return m_Hp;
}

std::string Player::getType() const {
    return m_Type;
}

void Player::setHp(const int &newHp) {
    m_Hp = newHp;
}

void Player::setCardToGet(const std::string &cardToGet) {
    m_CardToGet = cardToGet;
}

void Player::setRestrictedSuit(const std::string &restrictedSuit) {
    m_RestrictedSuit = restrictedSuit;
}

void Player::setOpponent(const std::shared_ptr <Player> &player) {
    m_Opponent = player;
}

std::shared_ptr <Player> Player::getOpponent() const {
    return m_Opponent;
}
