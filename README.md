# CountDown
Arduino Library to implement a CountDown clock (in SW polling, no HW timer).

## Description
The main functions of the CountDown clock are:

* *void start(ticks);*
* *void start(days, hours, minutes, seconds);*
* *void stop();*
* *void cont();*  (continue is a C-Keyword)*
* *uint32_t remaining();*
* *bool isRunning();*

These functions work straightforward.

The function **start(days, hours, minutes, seconds)** has changed its
parameters to uint32_t in 0.2.0.
This allows the user to call start with e.g. four hundred minutes **start(0, 0, 400, 0)** 
or a million seconds **start(0, 0, 0, 1000000)** as parameter.

Note: the function *start()* does not check if the parameters cause an overflow
in the underlying math.

## Operation
The Countdown clock uses by default **millis()** to do the time keeping,
although this can be changed runtime by **setResolution(res)**. The parameter 
**res** can be:
* *MICROS*
* *MILLIS*
* *SECONDS*  // wrapper around millis()

Although possible one should not change the resolution of the CountDown 
clock while it is running as you mix up different timescales.

One can call **start(...)** at any time to reset the running clock to
a new value. This allows to implement a sort of watchdog clock in which e.g. 
the user must press a button at least once per minute to show he is still
awake.


