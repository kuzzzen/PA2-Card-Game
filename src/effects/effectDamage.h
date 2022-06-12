#ifndef EFFECTDAMAGE_H
#define EFFECTDAMAGE_H

#include "effect.h"

/// Deals damage to opponent
class EffectDamage : public Effect {
public:
    explicit EffectDamage(const int &value_);

    [[nodiscard]] int getValue() const;

    [[nodiscard]] std::shared_ptr <Effect> getPtr() const override;

    [[nodiscard]] std::string getStringRep() const override;

    void onPlayedBy(const std::shared_ptr <Player> &player) const override;

private:
    int m_Value;
};

#endif
