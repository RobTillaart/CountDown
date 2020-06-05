#pragma once
//
//    FILE: CountDown.h
//  AUTHOR: Rob Tillaart
// PURPOSE: CountDown library for Arduino
// HISTORY: See CountDown.cpp
//     URL: https://github.com/RobTillaart/CountDown
//

#include "Arduino.h"

#define COUNTDOWN_LIB_VERSION "0.2.1"

class CountDown
{
public:
    enum Resolution { MILLIS, MICROS, SECONDS };

    explicit CountDown(const enum Resolution res = MILLIS);
    void setResolution(const enum Resolution res = MILLIS);

    void start(uint32_t ticks);
    void start(uint16_t days, uint32_t hours, uint32_t minutes, uint32_t seconds);
    void stop();
    void cont();

    uint32_t remaining();
    bool isRunning() const              { return _state == CountDown::RUNNING; };
    enum Resolution resolution() const  { return _res; };

private:
    enum State { RUNNING, STOPPED };

    uint32_t _ticks;
    uint32_t _remaining;
    enum State _state;
    enum Resolution _res;
    unsigned long _starttime;

    void calcRemaining();
    uint32_t (*_gettime)(void);
    static uint32_t seconds() { return millis() / 1000; };
    // static uint32_t seconds();  // TODO
};

// -- END OF FILE --
