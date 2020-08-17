
int driveMotor = 3; //PWM output for speed controller
int motorDutyCycle = 0; //variable to be used for code
int gateDir = 2; //Gate direction output for speed controller

int gateInput = 7; //Input for gate open/close demand
int gateInputExtra = 8; //Input for gate open/close demand extra
int gateControl = 0; //Variable is debounced from 0/1 to be used to begin accel/decel sequence
int openCommand =0; //Variable goes from 0/1 if gateInput and gateInputExtra are high 

int gateOpen = 4; //Switch input when gate is open
int gateClosed = 5; //Switch input when gate is closed

int gateEmergency = 6; //Switch either end of gate to stop over travel

bool rampUp = false; //Gate state - accel up to speed
bool rampDown = false; //Gate state - decel to a stop

//Debounce related
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000;

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

//Debounce gateControl variable 
if (openCommand != lastButtonState){
  lastDebounceTime = millis();
}

if ((millis() - lastDebounceTime) > debounceDelay) {   
gateControl = openCommand;
}
if (openCommand != lastButtonState){
  lastButtonState = openCommand;
}

if (digitalRead(gateInput) == HIGH && (digitalRead(gateInputExtra) == HIGH)) {
  openCommand = 1;
}
if(digitalRead(gateInput) == LOW && (digitalRead(gateInputExtra) == LOW)) {
  openCommand = 0;
}


//Safety switch to prevent overrun/ can be pressed to stop gate from running
if (digitalRead(gateEmergency) == HIGH &&motorDutyCycle >0){
motorDutyCycle = 0;
rampUp = false;
rampDown = false;
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



}

if(rampUp == true && motorDutyCycle < 255) {
  motorDutyCycle = motorDutyCycle +1;
}

if(rampDown == true && motorDutyCycle > 0) {
  motorDutyCycle = motorDutyCycle -1;
}

analogWrite(driveMotor, motorDutyCycle); 

delay(10);

Serial.println(gateControl); 
delay(1);
}
