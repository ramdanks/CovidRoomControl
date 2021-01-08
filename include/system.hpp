#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ultrasonic.hpp"
#include "state.hpp"
#include "door.hpp"

#define DOOR_NONE     0
#define DOOR_ENTER    1
#define DOOR_EXIT     2
#define DOOR_EXTRA    3

#define LAYOUT_SINGLE 0
#define LAYOUT_DOUBLE 1

#define LCD_CLEAR(lcd)     lcd->clear();
#define LCD_PRINT(lcd,x,y) lcd->clear(); lcd->print(x); lcd->setCursor(0,1); lcd->print(y)

class System
{
public:
    // layout pin
    System();
    System(byte pin);
    System(const System& other) = delete;

    void init_motordis(byte pin);
    void init_buzz(byte pin);
    void init_door(byte left, byte right);
    void init_led(byte full, byte response);
    void init_echo(byte in_echo, byte in_trig, byte out_echo, byte out_trig);
    void set_bound_in(uint16_t lo, uint16_t hi);
    void set_bound_out(uint16_t lo, uint16_t hi);

    int process(State& s, LiquidCrystal* lcd = nullptr);
    void print_population(State& s, LiquidCrystal* lcd);
    bool read_layout();

private:
    void open_door(Door& d);
    void shut_door(Door& d);
    void inline full_indicator();
    void inline led_full();
    void inline led_resp();
    void inline led_reset();
    void inline led_warn();

    bool m_layout;
    byte m_buzz;
    byte m_dis;
    byte m_ledfull, m_ledresp;
    Door m_door, m_door2;
    Echo m_echoin, m_echoout;
};