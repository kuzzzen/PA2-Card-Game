#include "effectGetCard.h"

EffectGetCard::EffectGetCard(std::string card) : Effect("getCard", 2), m_CardToTake(std::move(card)) {}

std::string EffectGetCard::getCard() const {
    return m_CardToTake;
}

std::shared_ptr <Effect> EffectGetCard::getPtr() const {
    return std::make_shared<EffectGetCard>(*this);
}

void EffectGetCard::onPlayedBy(const std::shared_ptr <Player> &player) const {
    player->getOpponent()->getOpponent()->setCardToGet(m_CardToTake);
}

std::string EffectGetCard::getStringRep() const {
    return m_CardToTake;
}