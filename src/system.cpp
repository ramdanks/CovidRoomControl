#include "system.hpp"

System::System()
    : m_ledresp(0), m_ledfull(0), m_layout(LAYOUT_SINGLE)
{
}

System::System(byte pin)
    : m_ledresp(0), m_ledfull(0)
{
    pinMode(pin, INPUT);
    m_layout = digitalRead(pin);
}

void System::init_motordis(byte pin)
{
    m_dis = pin;
    pinMode(pin, OUTPUT);
}

void System::init_buzz(byte pin)
{
    m_buzz = pin;
}

void System::init_door(byte left, byte right)
{
    if (m_layout == LAYOUT_SINGLE)
    {
        m_door.init(left, right);
    }
    else if (m_layout == LAYOUT_DOUBLE)
    {      
        m_door.init(left);
        m_door2.init(right);
    }
}

void System::init_led(byte full, byte response)
{
    m_ledfull = full;
    m_ledresp = response;
}

void System::init_echo(byte in_echo, byte in_trig, byte out_echo, byte out_trig)
{
    m_echoin.init(in_echo, in_trig);
    m_echoout.init(out_echo, out_trig);
}

void System::set_bound_in(uint16_t lo, uint16_t hi)
{
    m_echoin.set_bound(lo, hi);
}

void System::set_bound_out(uint16_t lo, uint16_t hi)
{
    m_echoout.set_bound(lo, hi);
}

int System::process(State& s, LiquidCrystal* lcd)
{
    print_population(s, lcd);
    bool exit = false; // save previous state
    bool enter = false; // save previous state
    bool in, out;

    if (m_layout == LAYOUT_SINGLE)
    {
        do
        {
            in = m_echoin.detect();
            delay(10); // sound still in the air, wait till gone
            out = m_echoout.detect();

            // process enter and exit sequentially
            if (!enter)
            {
                // always accept from inside
                if (in)
                {
                    exit = true;
                    open_door(m_door);
                }
                // wait until not detected
                else if (exit && !out)
                {
                    exit = false;
                    shut_door(m_door);
                    s.decrement();
                    print_population(s, lcd);
                }
            }
            if (!exit)
            {
                // accept from outside only if not full
                if (out && s.get_state() == FULL)
                {
                    full_indicator();
                }
                else if (out)
                {
                    enter = true;
                    open_door(m_door);
                }
                // wait until not detected
                else if (enter && !in)
                {
                    enter = false;
                    shut_door(m_door);
                    s.increment();
                    print_population(s, lcd);
                }
            }
        } while (in || out);
    }
    else if (m_layout == LAYOUT_DOUBLE)
    {
        auto& door_enter = m_door2;
        auto& door_exit = m_door;
        do
        {
            in = m_echoin.detect();
            delay(10); // sound still in the air, wait till gone
            out = m_echoout.detect();

            // always accept from inside
            if (in)
            {
                exit = true;
                open_door(door_exit);
            }
            else if (exit)
            {
                exit = false;
                shut_door(door_exit);
                s.decrement();
                print_population(s, lcd);
            }
            // accept from outside only if not full
            if (out && s.get_state() == FULL)
            {
                full_indicator();
            }
            else if (out)
            {
                enter = true;
                open_door(door_enter);
            }
            else if (enter)
            {
                enter = false;
                shut_door(door_enter);
                s.increment();
                print_population(s, lcd);
            }
        } while (in || out);
    }

    led_reset();
    return 0;
}

void System::print_population(State& s, LiquidCrystal* lcd)
{
    static char* pop_str = new char[16];
    static uint16_t count_prev = 0xFFFF;
    auto count = s.get_count();

    if (count_prev != count)
    {
        count_prev = count;
        snprintf(pop_str, 16, "COUNT:%d/%d", count, s.limit);
        LCD_PRINT(lcd, "POPULATION METER", pop_str);
    }
}

bool System::read_layout()
{
    return m_layout;
}

void System::open_door(Door& d)
{
    if (d.is_closed())
    {
        led_resp();
        digitalWrite(m_dis, HIGH);
        tone(m_buzz, 1500);
        delay(200);
        tone(m_buzz, 1800);
        delay(200);
        noTone(m_buzz);
        digitalWrite(m_dis, LOW);
        d.open();
    }
}

void System::shut_door(Door& d)
{
    if (d.is_opened())
    {
        led_warn();
        tone(m_buzz, 600);
        d.close();
        noTone(m_buzz);
    }
}

void System::full_indicator()
{
    led_full();
    tone(m_buzz, 600);
    delay(500);
    tone(m_buzz, 1000);
    delay(500);
    noTone(m_buzz);
}

void System::led_full()
{
    digitalWrite(m_ledresp, LOW);
    digitalWrite(m_ledfull, HIGH);
}

void System::led_resp()
{
    digitalWrite(m_ledresp, HIGH);
    digitalWrite(m_ledfull, LOW);
}
void System::led_reset()
{
    digitalWrite(m_ledresp, LOW);
    digitalWrite(m_ledfull, LOW);
}
void System::led_warn()
{
    digitalWrite(m_ledresp, HIGH);
    digitalWrite(m_ledfull, HIGH);
}