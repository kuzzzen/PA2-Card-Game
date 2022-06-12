#ifndef EFFECTHEALING_H
#define EFFECTHEALING_H

#include "effect.h"

/// Gives you +mentioned health (no more than 100)
class EffectHealing : public Effect {
public:
    explicit EffectHealing(const int &value_);

    [[nodiscard]] int getValue() const;

    [[nodiscard]] std::shared_ptr <Effect> getPtr() const override;

    [[nodiscard]] std::string getStringRep() const override;

    void onPlayedBy(const std::shared_ptr <Player> &player) const override;

private:
    int m_Value;
};

#endif
