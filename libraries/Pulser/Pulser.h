#ifndef _PULSER__H_
#define _PULSER__H_

#include <StateMachine.h>

/**
 * Pulser
 *
 * This class extends the StateMachine class to provide a boolean output which
 * alternates between true and false with separate durations for the two states.
 * A Pulser object is defined to be a real-time StateMachine object.
 */
class Pulser : public StateMachine
{
    protected:
        const unsigned long m_onTime;   // in true state for this many msec
        const unsigned long m_offTime;  // in false state for this many msec
        unsigned long m_switchTime;     // clock time of last state transition
        bool m_state;                   // current state
        
    public:
        /**
         * Constructor
         *
         * @param onTime duration of true (on) state in milliseconds
         * @param offTime duration of false (off) state in milliseconds
         */
        Pulser(
            const unsigned int onTime, 
            const unsigned int offTime
        );
        
        /**
         * Get the current state
         */
        bool read() const;
        
        /**
         * Update this object's state
         *
         * @return true if object's state was updated
         */
        virtual bool update();
};

#endif
