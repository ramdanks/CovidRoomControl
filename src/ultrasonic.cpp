#include "ultrasonic.hpp"

Echo::Echo(byte echo, byte trig)
    : m_echo(echo), m_trig(trig)
{
    pinMode(m_echo, INPUT);
    pinMode(m_trig, OUTPUT);
}
    
void Echo::init(byte echo, byte trig)
{
    m_echo = echo;
    m_trig = trig;
    pinMode(m_echo, INPUT);
    pinMode(m_trig, OUTPUT);
}

void Echo::set_bound(uint16_t lo_cm, uint16_t hi_cm)
{
    mLoBound = lo_cm * CALIB_FACTOR;
    mUpBound = hi_cm * CALIB_FACTOR;
}

bool Echo::detect()
{
    return measure_duration() != 0;
}

uint32_t Echo::measure_cm()
{
    uint32_t deltaTime = send_ultrasonic(10);
    if (deltaTime > mUpBound || deltaTime < mLoBound)
        return 0;
    return to_cm(deltaTime);
}

uint32_t Echo::measure_duration()
{
    uint32_t deltaTime = send_ultrasonic(10);
    if (deltaTime > mUpBound || deltaTime < mLoBound)
        return 0;
    return deltaTime;
}

uint32_t Echo::to_cm(uint32_t microsec)
{
    return microsec / CALIB_FACTOR;
}

uint32_t Echo::send_ultrasonic(byte impulse_time)
{
    digitalWrite(m_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trig, HIGH);
    delayMicroseconds(impulse_time);
    digitalWrite(m_trig, LOW);
    return pulseIn(m_echo, HIGH);
}