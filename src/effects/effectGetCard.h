#ifndef EFFECTGETCARD_H
#define EFFECTGETCARD_H

#include "effect.h"
#include "../players/player.h"


/// Player gets copy of mentioned card
class EffectGetCard : public Effect {
public:
    explicit EffectGetCard(std::string card);

    /// Returns name of card to take
    [[nodiscard]] std::string getCard() const;

    [[nodiscard]] std::shared_ptr <Effect> getPtr() const override;

    [[nodiscard]] std::string getStringRep() const override;

    void onPlayedBy(const std::shared_ptr <Player> &player) const override;

private:
    std::string m_CardToTake;
};

#endif
