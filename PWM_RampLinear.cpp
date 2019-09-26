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
    _pin = pin;
}

void PWM_RampLinear::ramp(uint8_t targValue, uint16_t duration){
    if (_isRamping == false){

        // If the ramping process is not active, map the new values
        
        _targValue = targValue;
        if (_targValue == _currValue){return;}
        //else if (_targValue < _currValue){_changeValue = _currValue - _targValue;} // ramp down
        //else if (_targValue > _currValue){_changeValue = _targValue - _currValue;} // ramp up
        //else return;
	_changeValue = _targValue - _currValue;
	_prevValue = _currValue;
        _duration = duration;
        _elapsedMillis = 0;
        _prevMillis = millis();
        // Latch/set the flag
        _isRamping = true;
        

    }
}

void PWM_RampLinear::update(void){
    // if the ramping is not active, just exit
    if (_isRamping == false){
        return;
    }
    else{
        
        // Track the elapsed millis since the ramp() was first called
        _elapsedMillis = millis() - _prevMillis;
        // Caluclate the new value based on what percentage of the duration the elapsed time is
        //if (_targValue < _currValue){ _currValue = 255 - ((_changeValue * _elapsedMillis) / _duration); }
        //else { _currValue = ((_changeValue * _elapsedMillis) / _duration); }
        _currValue = ((_changeValue * _elapsedMillis) / _duration) + _prevValue;

        // Clamp the PWM to valid numbers
        if (_currValue > 255){_currValue = 255;}
        if (_currValue <   0){_currValue = 0;}
        // If the process is finished or time is up
        if ((_currValue == _targValue) || (_elapsedMillis >= _duration)){
            // Force the value, just in case
            _currValue = _targValue;
            // Unlatch the flag
            _isRamping = false;
        }
        // as long as ramping is active, write to the output, otherwise don't bother wasting resources
        analogWrite(_pin, _currValue);
        
    }
}
