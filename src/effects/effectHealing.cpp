#include "effectHealing.h"
#include "../players/player.h"

EffectHealing::EffectHealing(const int &value_) : Effect("healing", 1), m_Value(value_) {}

int EffectHealing::getValue() const {
    return m_Value;
}

std::shared_ptr <Effect> EffectHealing::getPtr() const {
    return std::make_shared<EffectHealing>(*this);
}

void EffectHealing::onPlayedBy(const std::shared_ptr <Player> &player) const {
    int hp = m_Value + player->getHp();
    player->getOpponent()->getOpponent()->setHp(hp > 100 ? 100 : hp); // :)
}

std::string EffectHealing::getStringRep() const {
    return std::to_string(m_Value);
}
