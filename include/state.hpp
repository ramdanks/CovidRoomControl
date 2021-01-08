#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

enum eState
{
    EMPTY,
    POPULATED,
    FULL,
};

class State
{
public:
    uint16_t limit;

    eState get_state();
    void update();

    uint16_t get_count();
    void increment();
    void decrement();

private:
    uint16_t m_count;
};