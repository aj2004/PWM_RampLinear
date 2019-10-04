/* PWM_RampLinear.cpp - Library Source file
 *
 * by Kevin W. <aj2004@shaw.ca>
 *
 *
 * This library will allow a PWM pin to be gradually
 * changed to a different 8-bit value over a given
 * length of time.
 * 
 */
#include "Arduino.h"
#include "PWM_RampLinear.h"

PWM_RampLinear::PWM_RampLinear (uint8_t pin){
    _pin = pin; // privatize the pin
    _currValue = 0; // initialize the currValue
    analogWrite(_pin, _currValue); // initialize the brightness

}

void PWM_RampLinear::ramp(uint8_t targValue, uint16_t duration){
    if (_isRamping == false){

        // If the ramping process is not already active, map the new values
        _targValue = targValue;
        if (_targValue == _currValue){return;}
        // privatize this variable
        _duration = duration;
        // calculate the difference in brightnesses
	    _changeValue = _targValue - _currValue;
        // reset the _prevValue
	    _prevValue = _currValue;
        // reset the _elapsedMillis
        _elapsedMillis = 0;
        // reset the _prevMillis
        _prevMillis = millis();
        // Latch/set the flag to prevent this code from running again until ramping is done
        _isRamping = true;

    }
}

void PWM_RampLinear::update(void){
    // if the ramping is not active, just exit
    if (_isRamping == false){
        // first clear the one-shot DONE bit
        rampDoneOS = false;
        return;
    }
    else{
        
        // Track the elapsed millis since the ramp() was first called
        _elapsedMillis = millis() - _prevMillis;
        // Calculate the new value based on what percentage of the duration the elapsed time is
        _currValue = ((_changeValue * _elapsedMillis) / _duration) + _prevValue;
        // Clamp the PWM to valid numbers
        if (_currValue > 255){_currValue = 255;}
        if (_currValue <   0){_currValue = 0;}
        // If the values are equal or time is up
        if ((_currValue == _targValue) || (_elapsedMillis >= _duration)){
            // Force the value, just in case
            _currValue = _targValue;
            // Unlatch the flag
            _isRamping = false;
            // Turn on a one-shot DONE bit
            rampDoneOS = true;
        }
        // as long as ramping is active, write to the output
        analogWrite(_pin, _currValue);
        
    }
}
