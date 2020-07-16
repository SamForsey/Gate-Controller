
int driveMotor = 3; //PWM output for speed controller
int motorDutyCycle = 0;
int gateDir = 13; //Gate direction output for speed controller

int gateInput = 2; //Input for gate open/close demand
int gateControl = 0; //Variable to be used for code

int gateOpen = 4; //Switch input when gate is open
int gateClosed = 5; //Switch input when gate is closed

int gateEmergency = 6; //Switch either end of gate to stop over travel

bool rampUp = false; //Gate state - accel up to speed
bool rampDown = false; //Gate state - decel to a stop


void setup() {
  // put your setup code here, to run once:
pinMode(driveMotor, OUTPUT);
pinMode(gateInput, INPUT);
pinMode(gateOpen, INPUT);
pinMode(gateClosed, INPUT);
pinMode(gateDir, OUTPUT);
pinMode(gateEmergency, INPUT);

Serial.begin(9600);     

}

void loop() {
  // put your main code here, to run repeatedly:

if (digitalRead(gateInput) == HIGH) {
  gateControl = 1;
  
}
if(digitalRead(gateInput) == LOW) {
  gateControl = 0;
  
}

//Gate Opening ramp up
if (gateControl == 1 &&digitalRead(gateClosed) == HIGH &&motorDutyCycle == 0) { //Gate must be closed and stationary in order to begin opening
rampUp = true; 
rampDown = false;
digitalWrite(gateDir, HIGH);

}
//Gate opening ramp down
if (digitalRead (gateOpen) == HIGH && digitalRead(gateDir) == HIGH &&motorDutyCycle >0 ) { //gate hits closing switch, and gate is moving, then decel happens
rampUp = false;
rampDown = true;


}

//Gate closing ramp up
if (gateControl == 1 &&digitalRead(gateOpen) == HIGH &&motorDutyCycle == 0) { //Gate must be open in order to begin closing
rampUp = true; 
rampDown = false;
digitalWrite(gateDir, LOW);

}

//Gate closing ramp down
if (digitalRead (gateClosed) == HIGH && digitalRead(gateDir) == LOW &&motorDutyCycle >0) { //gate hits closing switch, and gate is moving, then decel happens
rampUp = false;
rampDown = true;
digitalWrite(gateDir, LOW);


}

if(rampUp == true && motorDutyCycle < 255) {
  motorDutyCycle = motorDutyCycle +1;
}

if(rampDown == true && motorDutyCycle > 0) {
  motorDutyCycle = motorDutyCycle -1;
}

analogWrite(driveMotor, motorDutyCycle); 

delay(10);

Serial.println(digitalRead(gateOpen)); 
delay(1);
}
