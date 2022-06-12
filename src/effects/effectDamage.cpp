#include "effectDamage.h"
#include "../players/player.h"

EffectDamage::EffectDamage(const int &value_) : Effect("damage", 0), m_Value(value_) {}

int EffectDamage::getValue() const {
    return m_Value;
}

std::shared_ptr <Effect> EffectDamage::getPtr() const {
    return std::make_shared<EffectDamage>(*this);
}

void EffectDamage::onPlayedBy(const std::shared_ptr <Player> &player) const {
    player->getOpponent()->setHp(player->getOpponent()->getHp() - m_Value);
}

std::string EffectDamage::getStringRep() const {
    return std::to_string(m_Value);
}
