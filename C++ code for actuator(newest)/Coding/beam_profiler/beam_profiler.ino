#include <uStepper.h>
#include <uStepperServo.h>

 #include <UStepper.h>

#define MAXACCELERATION 1500         //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY 1100           //Max velocity = 1100 steps/s

#define MIN_PIN 2
float stepCountAngle = 0;
float stepCount = 0;

float stepCountAngleNeg = 0;
float stepCountNeg = 0;
float currentSpeed ;
String state;
float y = 8000/360;

uStepper stepper(MAXACCELERATION, MAXVELOCITY);

void setup() {
  // put your setup code here, to run once:
  stepper.setup(NORMAL, QUARTER);
  Serial.begin(115200);
  //stepper.runContinous(CCW);
  pinMode(MIN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MIN_PIN), haltStepMin, FALLING);
}

void loop() {
  while (!Serial.available());
  
    state = Serial.readString(); // used to read incoming data
    int movement = state.toInt();
    int reverseMovement = -movement;
    Serial.flush();
    if (movement > 0){
      stepper.moveSteps(movement, CW, SOFT);
      delay(300);
      currentSpeed = stepper.encoder.getSpeed();
      while(currentSpeed!=0){
        currentSpeed = stepper.encoder.getSpeed();
        Serial.flush();
      }
      
    } else if (movement < 0) {
      stepper.moveSteps(reverseMovement, CCW, SOFT);
      delay(300);
      currentSpeed = stepper.encoder.getSpeed();
      while(currentSpeed!=0){
        currentSpeed = stepper.encoder.getSpeed();
        Serial.flush();
      }
    } else if (movement == 0) {
      stepper.runContinous(CCW);
      delay(300);
      currentSpeed = stepper.encoder.getSpeed();
      while(currentSpeed!=0){
        currentSpeed = stepper.encoder.getSpeed();
        Serial.flush();
      }
    }
      stepCountAngle = stepper.encoder.getAngleMoved();
      stepCount = stepCountAngle * y;
      Serial.println(stepCount, 2);
      delay(500);
      Serial.flush();
  
}

void haltStepMin() {
  bool motorState = stepper.getMotorState();
  if (motorState = true) {
    stepper.hardStop(SOFT);
  }
  stepper.encoder.setHome();
  delay(1000);
  stepper.moveSteps(400, CW, SOFT);
  delay(1000);

}
