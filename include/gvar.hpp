#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "state.hpp"
#include "system.hpp"

struct gvar
{
    gvar() = delete;
    gvar(const gvar& other) = delete;

    static State state;
    static System* system;
    static LiquidCrystal* lcd;
};

LiquidCrystal* gvar::lcd;
System* gvar::system;
State gvar::state;