#include "effect.h"

Effect::Effect(std::string type, const uint8_t &index)
        : m_Type(std::move(type)), m_Index(index) {}

uint8_t Effect::getIndex() const {
    return m_Index;
}
