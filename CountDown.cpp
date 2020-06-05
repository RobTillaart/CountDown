//
//    FILE: CountDown.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: CountDown library for Arduino
//
// HISTORY:
// 0.2.1   2020-06-05 fix library.json
// 0.2.0   2020-03-29 #pragma once, removed pre 1.0 support
// 0.1.3 - 2017-07-16 TODO improved seconds - OdoMeter see below ... TODO 
// 0.1.2 - 2017-07-16 added start(days, hours, minutes, seconds) + cont() == continue countdown
// 0.1.1 - 2015-10-29 added start(h, m, s)
// 0.1.0 - 2015-10-27 initial version
//

#include "CountDown.h"

CountDown::CountDown(const enum Resolution res)
{
  setResolution(res);
  stop();
}

void CountDown::setResolution(const enum Resolution res)
{
  _res = res;
  switch(_res)
  {
  case MICROS:
    _gettime = micros;
    break;
  case SECONDS:
    _gettime = seconds;
    break;
  case MILLIS:
  default:
    _gettime = millis;
    break;
  }
  _ticks = 0;
}

void CountDown::start(uint32_t ticks)
{
  _state = CountDown::RUNNING;
  _starttime = _gettime();
  _ticks = ticks;
}

void CountDown::start(uint16_t days, uint32_t hours, uint32_t minutes, uint32_t seconds)
{
  uint32_t ticks = 86400UL * days + 3600UL * hours + 60UL * minutes + seconds;
  if (ticks > 4294967) ticks = 4294967;  // prevent underlying millis() overflow
  setResolution(SECONDS);
  start(ticks);
}

void CountDown::stop()
{
  calcRemaining();
  _state = CountDown::STOPPED;
}

void CountDown::cont()
{
  if (_state == CountDown::STOPPED)
  {
    start(_remaining);
  }
}

uint32_t CountDown::remaining()
{
  calcRemaining();
  return _remaining;
}

void CountDown::calcRemaining()
{
  if (_state == CountDown::RUNNING)
  {
    uint32_t t = _gettime() - _starttime;
    _remaining = _ticks > t ? _ticks - t: 0;
    if (_remaining == 0)
    {
      _state = CountDown::STOPPED;
    }
  }
}

// TODO
// thanks to odometer - larger range
// https://forum.arduino.cc/index.php?topic=356253.msg2456606#msg2456606
// static uint32_t CountDown::seconds()
// {
  // static uint32_t count = 0UL;
  // static uint32_t offset = 0UL;
  // uint32_t now = millis();
  // uint32_t excess = now - offset;
  // if (excess >= 1000UL)
  // {
    // excess /= 1000UL; // convert to whole seconds
    // offset += (excess * 1000UL);
    // count += excess;
  // }
  // return count;
// }

// -- END OF FILE --
