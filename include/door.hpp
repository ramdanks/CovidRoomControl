#pragma once
#include <Arduino.h>
#include <Servo.h>

#define DOOR_DOUBLE_SIDED 1
#define DOOR_SINGLE_SIDED 0

class Door
{
public:
    Door() = default;
    Door(byte left, byte right = 0);
    Door(const Door& other) = delete;

    void init(byte left, byte right = 0);
    
    bool is_opened();
    bool is_closed();
    bool get_mode();

    bool open();
    bool close();

private:
    bool m_sided;
    bool m_opened;
    Servo m_left, m_right;
};