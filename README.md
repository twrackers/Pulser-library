# Pulser #

The `Pulser` class is derived from the `StateMachine` class ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).  A *Pulser* object toggles periodically between 'on' and 'off' states (implemented with booleans `true` and `false`), with separate on and off durations specified in milliseconds.  The *Pulser* class can be further subclassed to provide more functionality, such as turning an LED on and off.

## Examples ##

The `Pulser` library includes a few example sketches in the `examples` directory.

- `LED_Pulser` defines a *Strobe* class derived from *Pulser*, which includes a GPIO pin number in the object, as well as the on and off times used by the *Pulser*.  The *Strobe* object sets that GPIO pin to `OUTPUT` mode, then toggles it between `HIGH` (on) and `LOW` (off).  As the sketch's name implies, this can be used to drive an LED connected to the GPIO pin.  The example sketch defines three *Strobe* objects on GPIO pins 6, 5, and 3, with on-times of 10, 12, and 14 milliseconds respectively, and off-times of 990 milliseconds for all three.
- `LED_Beacon` is like `LED_Pulser`, except it defines a *Beacon* class.  A *Beacon*, like a *Strobe*, is given a GPIO pin number, on time, and off time.  In addition, a *Beacon* object gets "fade-on" and "fade-off" times, which set how many milliseconds the *Beacon* will take to go between full-off and full-on.  This is done by using GPIO pins which support PWM (pulse width modulation).  The `LED_Beacon` sketch requires the `FadeLED` library ([https://github.com/twrackers/FadeLED-library](https://github.com/twrackers/FadeLED-library)) be installed.
- `Pulser_and_Servo` defines the same *Strobe* class as that used in `LED_Pulser`. It also defines a *Sweep* class derived from *StateMachine*.  A *Sweep* object is given an amplitude and period (milliseconds) which will determine the movement of a servo motor attached to a GPIO pin (set using an `attach(int pin)` method).  The sketch defines three *Strobe* objects, a *Sweep* object, and a plain *Pulser*.  It then updates the *Strobe*s to control the LEDs, the *Pulser* to set the direction of the servo's movement, and the *Sweep* to move the servo in a smooth motion from one position to the other.  For a little fun, use red, white, and blue LEDs, attach a little paper flag to the servo's arm, and play "Stars and Stripes Forever". :)  The `Pulser_and_Servo` sketch requires the `Servo` library, which is part of the standard Arduino IDE install.

## Dependencies ##

The `Pulser` library itself depends on the `StateMachine` library.  Additional dependencies in the example sketches are described above.

## Installation ##

Instructions for installing the `Pulser` library can be found in file `INSTALL.md` at [https://github.com/twrackers/Pulser-library/blob/main/INSTALL.md](https://github.com/twrackers/Pulser-library/blob/main/INSTALL.md).
