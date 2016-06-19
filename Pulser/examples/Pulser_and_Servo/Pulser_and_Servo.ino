#include <Pulser.h>
#include <Servo.h>

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

class Sweep : public StateMachine
{
  private:
    Servo m_servo;            // embedded Servo object
    int m_pos;                // center position of sweep in degrees (45 to 135)
    int m_ampl;               // amplitude in degrees
    int m_half;               // half-cycle time
    unsigned long m_timeref;  // time when state changed
    bool m_state;             // true for ramp up, false for ramp down

  public:
    // Constructor
    Sweep(int amplitude, int period) :
      StateMachine(10, true),
      m_pos(90), m_ampl(amplitude),
      m_half(period / 2),
      m_timeref(millis()),
      m_state(true)
    {
    }

    void attach(int pin)
    {
      m_servo.attach(pin);
    }

    void setPosition(int pos)
    {
      m_pos = pos;
    }

    bool update()
    {
      if (StateMachine::update()) {
        unsigned long now = millis();
        if (now >= (m_timeref + m_half)) {
          m_state = !m_state;
          m_timeref = now;
        }
        int sw = map((now - m_timeref), 0, m_half, -m_ampl, m_ampl);
        if (m_state == false) {
          sw = -sw;
        }
        m_servo.write(m_pos + sw);
        return true;
      }
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

// Define a Sweep object.
Sweep sweep(30, 2000);   // sweep +/- 10 degrees, period 3 seconds

// Define a Pulser to alternate the sweep's center position
// between two values.
Pulser pulser(5000, 5000);

void setup()
{
  // Attach pin 9 to sweep.  Has to be done here instead of
  // in constructor if sweep object is global.
  sweep.attach(9);
}

void loop()
{
  // Update all the Strobe objects.
  StateMachine::updateAll(strobes, numStrobes);
  
  // Update the Pulser object, then use its state to
  // set the Sweep object's center position.
  pulser.update();
  sweep.setPosition(pulser.read() ? 80 : 100);
  
  // Update the Sweep object.
  sweep.update();
}

