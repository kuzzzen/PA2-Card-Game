#include "effectRestriction.h"
#include "../players/player.h"


EffectRestriction::EffectRestriction(std::string suit) : Effect("restriction", 3), m_SuitToBan(std::move(suit)) {}

std::string EffectRestriction::getRestrictions() const {
    return m_SuitToBan;
}

std::shared_ptr <Effect> EffectRestriction::getPtr() const {
    return std::make_shared<EffectRestriction>(*this);
}

void EffectRestriction::onPlayedBy(const std::shared_ptr <Player> &player) const {
    player->getOpponent()->setRestrictedSuit(m_SuitToBan);
}

std::string EffectRestriction::getStringRep() const {
    return m_SuitToBan;
}

