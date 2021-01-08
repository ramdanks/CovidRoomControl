#include "state.hpp"

eState State::get_state()
{
    if      (m_count == 0)     return eState::EMPTY;
    else if (m_count == limit) return eState::FULL;
    else                       return eState::POPULATED;
}

void State::update()
{

}

uint16_t State::get_count()
{
    return m_count;
}

void State::increment()
{
    if (m_count < limit)
    {
        m_count++;
        Serial.print("Population:");
        Serial.println(m_count);
    }
}

void State::decrement()
{
    if (m_count > 0x0000)
    {
        m_count--;
        Serial.print("Population:");
        Serial.println(m_count);
    }
}