/* PWM_Fade.h - Library Header file
 *
 *  by Kevin W. <aj2004@shaw.ca>
 *
 * This library will allow a PWM pin to be gradually
 * changed to a different 8-bit value over a given
 * length of time.
 * 
 */
#include "Arduino.h"
#ifndef PWM_RampLinear_h
#define PWM_RampLinear_h


class PWM_RampLinear{

    public:
        PWM_RampLinear (uint8_t pin);
        void ramp(uint8_t targValue, uint16_t duration);
        void update(void);
        
        
    private:
        bool _isRamping;
        uint8_t _pin;
        uint8_t _currValue;
        uint8_t _targValue;
        uint8_t _prevValue;
        int16_t _changeValue;
        uint16_t _duration;
        // Although _elapsedMillis should never get larger than _duration,
        // it MUST be big enough to hold (_elapsedMillis * _changeValue)
        uint32_t _elapsedMillis;
        uint32_t _prevMillis;

};

#endif
