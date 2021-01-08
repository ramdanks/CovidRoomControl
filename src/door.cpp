#include "door.hpp"

Door::Door(byte left, byte right)
{
    init(left, right);
}

void Door::init(byte left, byte right)
{
    m_left.attach(left);
    if (!right)
    {
        m_sided = DOOR_SINGLE_SIDED;
    }
    else
    {
        m_right.attach(right);
        m_sided = DOOR_DOUBLE_SIDED;
    }
    m_opened = true;
    close();
}

bool Door::is_opened()
{
    return m_opened;
}

bool Door::is_closed()
{
    return !m_opened;
}

bool Door::get_mode()
{
    return m_sided;
}

bool Door::open()
{
    if (m_opened) return false;
    
    if (m_sided == DOOR_DOUBLE_SIDED)
    {
        for (int i = 180; i >= 0; i--)
        {
            m_left.write(i);
            m_right.write(180-i);
            delay(15);
        }
    }
    else if (m_sided == DOOR_SINGLE_SIDED)
    {
        for (int i = 180; i >= 0; i--)
        {
            m_left.write(i);
            delay(15);
        }
    }

    m_opened = true;
    return true;
}

bool Door::close()
{
    if (!m_opened) return false;

    if (m_sided == DOOR_DOUBLE_SIDED)
    {
        for (int i = 0; i <= 180; i++)
        {
            m_left.write(i);
            m_right.write(180-i);
            delay(15);
        }
    }
    else if (m_sided == DOOR_SINGLE_SIDED)
    {
        for (int i = 0; i <= 180; i++)
        {
            m_left.write(i);
            delay(15);
        }
    }

    m_opened = false;
    return true;
}