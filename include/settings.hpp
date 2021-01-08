#pragma once
#include <Arduino.h>

#define LIMIT_POP 10
#define BAUD_RATE 9600

enum Pin
{
    ECHO_INSIDE  = A0,
    ECHO_OUTSIDE = A1,
    TRIG_INSIDE  = A2,
    TRIG_OUTSIDE = A3,
    MOTOR_DIS    = A4,
    LAYOUT       = A5,
    LED_RED      = 2,
    LED_YELLOW   = 3,
    BUZZER       = 4,
    SERVO_LEFT   = 5,
    SERVO_RIGHT  = 6,
    LCD_E        = 7,
    LCD_RS       = 8,
    LCD_RW       = 9,
    LCD_D4       = 10,
    LCD_D5       = 11,
    LCD_D6       = 12,
    LCD_D7       = 13,
};

enum EchoBound
{
    LOWER_BOUND = 30,
    UPPER_BOUND = 300,
};