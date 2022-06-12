#ifndef EFFECTRESTRICTION_H
#define EFFECTRESTRICTION_H

#include "effect.h"

/// Restricts opponent from playing specific suit next turn
class EffectRestriction : public Effect {
public:
    explicit EffectRestriction(std::string suit);

    /// Returns banned suit name
    [[nodiscard]] std::string getRestrictions() const;

    [[nodiscard]] std::shared_ptr <Effect> getPtr() const override;

    [[nodiscard]] std::string getStringRep() const override;

    void onPlayedBy(const std::shared_ptr <Player> &player) const override;

private:
    std::string m_SuitToBan;
};

#endif
