#include "gvar.hpp"
#include "settings.hpp"

void setup()
{
    // initialize communication
    Serial.begin(BAUD_RATE);
    gvar::lcd = new LiquidCrystal(Pin::LCD_RS,
                                  Pin::LCD_RW,
                                  Pin::LCD_E,
                                  Pin::LCD_D4,
                                  Pin::LCD_D5,
                                  Pin::LCD_D6,
                                  Pin::LCD_D7);
    gvar::lcd->begin(16, 2);
    LCD_PRINT(gvar::lcd, "Covid", "Room Control");

    // initialize pin
    gvar::state.limit = LIMIT_POP;
    gvar::system = new System(Pin::LAYOUT);
    gvar::system->init_buzz(Pin::BUZZER);
    gvar::system->init_motordis(Pin::MOTOR_DIS);
    gvar::system->init_led(Pin::LED_RED, Pin::LED_YELLOW);
    gvar::system->init_door(Pin::SERVO_LEFT, Pin::SERVO_RIGHT);
    gvar::system->init_echo(Pin::ECHO_INSIDE, Pin::TRIG_INSIDE, Pin::ECHO_OUTSIDE, Pin::TRIG_OUTSIDE);
    gvar::system->set_bound_in(EchoBound::LOWER_BOUND, EchoBound::UPPER_BOUND);
    gvar::system->set_bound_out(EchoBound::LOWER_BOUND, EchoBound::UPPER_BOUND);

    // check door layout on startup
    gvar::lcd->clear();
    gvar::lcd->print("LAYOUT MODE:");
    gvar::lcd->setCursor(0, 1);
    if ( gvar::system->read_layout() == LAYOUT_SINGLE )
    {
        gvar::lcd->print("HYBRID DOOR");
        Serial.println("Layout Mode: Hybrid Door");
    }
    else
    {
        gvar::lcd->print("SEPERATE DOOR");
        Serial.println("Layout Mode: Seperate Door");
    }  
    delay(2000);
}

void loop()
{
    gvar::system->process(gvar::state, gvar::lcd);
}