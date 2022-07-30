OVERVIEW

Gate controller was designed as a way to control a gate automatically; using safety switch inputs, limit switches and a keyfob to safely open and close the gate.

HOW IT WORKS

It uses an Arduino to output a PWM signal (driveMotor) to operate an electronic speed controller (ESC). 

Using a duty cycle variable (motorDutyCycle) the motor speed can be varied. It is ramped up and down from 0-100% gradually for smooth operation.

The motor will only be driven when certain conditions are met; the safety switches (gateEmergency) must not be pressed and the gate must be on a limit ramp. 
In this case the gate always knows which direction to ramp up (rampUP) in and when to decelerate (rampDOWN) to a stop.
