
int driveMotor = 3;
int gateControl = 2;
int gateOpen = 4;
int gateClosed = 5;
int gateDir = 13;

void setup() {
  // put your setup code here, to run once:

pinMode(driveMotor, OUTPUT);
pinMode(gateControl, INPUT);
pinMode(gateOpen, INPUT);
pinMode(gateClosed, INPUT);
pinMode(gateDir, OUTPUT);


Serial.begin(9600);                                                                                                                                          

}

void loop() {
  // put your main code here, to run repeatedly:

if (digitalRead(gateControl) == HIGH &&digitalRead(gateOpen) == HIGH) {

digitalWrite(gateDir, HIGH);
delay(250);
analogWrite(driveMotor, 0);
delay(250);
analogWrite(driveMotor, 12);
delay(250);
analogWrite(driveMotor, 25);
delay(250);
analogWrite(driveMotor, 64);
delay(250);
analogWrite(driveMotor, 127);
delay(250);
analogWrite(driveMotor, 191);
delay(250);
analogWrite(driveMotor, 255);

}

if (digitalRead (gateClosed) == HIGH && driveMotor >0) {
  
analogWrite(driveMotor, 255);
delay(250);
analogWrite(driveMotor, 191);
delay(250);
analogWrite(driveMotor, 127);
delay(250);
analogWrite(driveMotor, 64);
delay(250);
analogWrite(driveMotor, 25);
delay(250);
analogWrite(driveMotor, 12);
delay(250);
analogWrite(driveMotor, 0);
  
}

int buttonState = digitalRead(gateControl);
int dutyCycle = digitalRead(driveMotor);
Serial.println(buttonState); 

delay(1);
}
