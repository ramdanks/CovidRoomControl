#pragma once
#include <Arduino.h>

#define CALIB_FACTOR 58.2

class Echo
{
public:
    Echo() = default;
    Echo(byte echo, byte trig);
    
    // initialize specific port for ultrasonic sensor
    void init(byte echo, byte trig);
    // set boundaries to ignore when performing echo
    void set_bound(uint16_t lo_cm, uint16_t hi_cm);
    
    // return if echo detects an object
    bool detect();
    // return echo length in cm
    uint32_t measure_cm();
    // return echo time in microsec
    uint32_t measure_duration();

    // convert echo time to length
    static uint32_t to_cm(uint32_t microsec);

    // sending ultrasonic for echo
    uint32_t send_ultrasonic(byte impulse_time);

private:
    byte m_echo, m_trig;
    uint16_t mUpBound;
    uint16_t mLoBound;
};