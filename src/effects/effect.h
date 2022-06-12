#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <memory>

class Player;

/// Base class for all effects
class Effect {
public:
    explicit Effect(std::string type, const uint8_t & index);

    virtual ~Effect() noexcept = default;

    /// Returns effect index for GetEffectsAsString function in Card class
    [[nodiscard]] uint8_t getIndex() const;

    /// Returns shared_ptr to correct effect (to avoid using dynamic_cast too much)
    [[nodiscard]] virtual std::shared_ptr <Effect> getPtr() const = 0;

    /// Returns effect string representation for GetEffectsAsString function in Card class
    [[nodiscard]] virtual std::string getStringRep() const = 0;

    virtual void onPlayedBy(const std::shared_ptr <Player> &player) const = 0;

protected:
    std::string m_Type;
    uint8_t m_Index;
};

#endif
