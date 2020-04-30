#include <Pulser.h>

// Define class Strobe as a subclass of Pulser.
// In Object-Oriented-Programming speak, a Strobe "isa" Pulser,
// with the added attribute of an assigned GPIO pin, which will
// be used to drive an LED.
// The timing information is handled by the parent Pulser object.

class Strobe : public Pulser
{
  private:
    int m_pin;  // GPIO pin

  public:
    // Constructor -- create Pulser with GPIO pin
    Strobe(int pin, int on, int off) : Pulser(on, off), m_pin(pin)
    {
      // Initialize GPIO pin for output, set it to match strobe's
      // state (initially false, turning LED off).
      pinMode(m_pin, OUTPUT);
      digitalWrite(m_pin, Pulser::read() ? HIGH : LOW);
    }

    // Perform update on this Strobe.
    bool update()
    {
      // Time to update?
      if (Pulser::update()) {
        // If so, turn LED on or off, based on Strobe state.
        digitalWrite(m_pin, Pulser::read() ? HIGH : LOW);
        // We have updated.
        return true;
      }
      // Nope, no update this time around.
      return false;
    }
};

// Define three Strobe objects on 3 GPIO pins with slightly different timing.
// Note: the 3 GPIO pins selected are all PWM-capable, for the purposes of
// another demo sketch.
Strobe s1(6, 10, 990);
Strobe s2(5, 12, 990);
Strobe s3(3, 14, 990);

// Create an array of pointer-to-Strobe objects for the
// StateMachine::updateAll method.
int numStrobes = 3;
StateMachine* strobes[] = { &s1, &s2, &s3 };

void setup()
{
  // No further setup required.
}

void loop()
{
  // Update all the Strobe objects.
  StateMachine::updateAll(strobes, numStrobes);
}

