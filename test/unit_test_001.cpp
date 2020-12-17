//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the CountDown Library
//          https://github.com/RobTillaart/CountDown
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
#define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
#define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "CountDown.h"



unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  CountDown a(CountDown::MINUTES);
  CountDown b(CountDown::SECONDS);
  CountDown c(CountDown::MILLIS);
  CountDown d(CountDown::MICROS);

  assertEqual(CountDown::MINUTES, a.resolution());
  assertEqual(CountDown::SECONDS, b.resolution());
  assertEqual(CountDown::MILLIS,  c.resolution());
  assertEqual(CountDown::MICROS,  d.resolution());

  assertFalse(a.isRunning());
  assertFalse(b.isRunning());
  assertFalse(c.isRunning());
  assertFalse(d.isRunning());

  a.start(10);
  assertTrue(a.isRunning());
  a.stop();
  assertFalse(a.isRunning());
  a.cont();
  assertTrue(a.isRunning());
  a.stop();
  assertFalse(a.isRunning());
}


unittest(test_run)
{
  CountDown cd(CountDown::MILLIS);
  assertEqual(CountDown::MILLIS,  cd.resolution());

  assertFalse(cd.isRunning());
  cd.start(10);
  assertTrue(cd.isRunning());
  delay(5);
  cd.stop();
  assertFalse(cd.isRunning());
  assertEqual(5, cd.remaining());
}

unittest_main()

// --------
