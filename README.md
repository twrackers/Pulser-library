# Pulser library

This library is a derived subclass of the __StateMachine__ class, found in this repository at [Arduino-projects/libraries/StateMachine](https://github.com/twrackers/Arduino-projects/tree/master/libraries/StateMachine).  A Pulser object alternates periodically between two states, on and off, with separate on and off durations.  The Pulser class is intended to be further subclassed to provide the actual functionality desired by the user, for example to flash an LED on a digital output pin.

For an example of subclassing Pulser, see the example sketch [Arduino/sketches/LED_Pulser](https://github.com/twrackers/Arduino-projects/tree/master/sketches/LED_Pulser) in this repository.
