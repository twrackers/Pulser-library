#include <Pulser.h>

// Constructor
//
// An instance of this class runs with millisecond-resolution timing in soft
// real time (meaning nothing disastrous happens if an update cycle is a little
// late).
// A Pulser starts out in its false (off) state and changes to its true (on)
// state after the off time has elapsed for the first time.
Pulser::Pulser(
    const unsigned int onTime, 
    const unsigned int offTime
) : StateMachine(1, true),
    m_onTime(onTime), m_offTime(offTime), 
    m_switchTime(millis()), m_state(false)
{
}

// Gets the current state of the object.
bool Pulser::read() const
{
    return m_state;
}

// Performs the update cycle for this object.
bool Pulser::update()
{
    // If it's time to perform an update, ...
    if (StateMachine::update()) {
        // Get the current clock time.
        unsigned long msec = millis();
        // How long have we been in the current state?
        unsigned long d = msec - m_switchTime;
        // Has the current state's duration elapsed yet?
        if ((m_state && (long) (d - m_onTime) >= 0)
            || (!m_state && (long) (d - m_offTime) >= 0)) {
            // If so, toggle the state and mark the current clock time.
            m_state = !m_state;
            m_switchTime = msec;
        }
        // State is updated.
        return true;
    }
    // Not update time yet.
    return false;
}
