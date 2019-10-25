# PWM_RampLinear
Linear Ramping function that updates in background.

by aj2004

Original   : September 2, 2019

Last update: October 4, 2019

This library will linearly ramp a value to a given point over a given time and will update once per scan/loop.
Every time update() is called, the new 8-bit value is calculated by dividing the milliseconds elapsed since the ramp() function was called by the desired ramp duration, which equals the completed percentage of the ramp, and multiplying by the amount to change. This result is the amount to change for this iteration. Add this to the original value to get the new value.

Originally, I wrote this code to fade an LCD backlight off when idle for some time, and back on when a button is pressed (to 'wake' it up). I use the I2C-backpack LCDs from eBay. Mine have a jumper on the backpack module which connects the backlight Anode to +5V and on/off control is done via code `lcd.backlight();` or `lcd.noBacklight();`. This jumper may be removed and the non-5V pin (that is, the LCD Anode pin) wired to a PWM output. The code control of the backlight must still be used to enable/disable the backlight, but this way allows brightness control.

------
### Note:
This library could/should be modified to work with values other than the PWM's 8-bit limit. It could/should also allow for any function as an argument in the constructor, rather than strictly "analogWrite(pin, value)". However, allowing for, say, a 16-bit value would cause greater memory usage since several variables would need to be enlarged.

------
## Pseudo Code
__.ramp() function - to initiate a ramping (one-shot latched/lockout until done):__

`prevValue = currValue`

`changeValue = targValue - prevValue (-255 ... +255)`

__.update() function - runs once per loop() until done, then unlatch:__

`currValue = (changeValue * elapsedMillis / duration) + prevValue`

`analogWrite(pin, currValue)`

------
## Usage

1. Create an object:
  (led connected to pin 9 (pwm) and GND or +V)
  
  `PWM_RampLinear myFadingLED(9);`
  
2. Trigger a ramp when e.g. motion is detected:

  `if(motionSensorTriggered){`
  `  myFadingLED.ramp(targetValue8bit, milliseconds);`
  `}`
    
3. In the main loop():
  `myFadingLED.update();`
