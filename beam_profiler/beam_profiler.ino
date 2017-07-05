#include <uStepper.h>

#define MAXACCELERATION 1500      //Max acceleration = 1500 Steps/s^2
#define MAXVELOCITY   1100        //Max velocity = 1100 steps/s

#define MIN_PIN 2
/*******************************this code is the interupt bit
********************************************/

float stepCountAngle = 0;
float stepCount = 0;

float stepCountAngleNeg = 0;
float stepCountNeg = 0;

String state;
float y = 8000/360;
bool flag;
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
      delay(movement);
      stepCountAngle = stepper.encoder.getAngleMoved();
      stepCount = stepCountAngle * y;
      delay(2000);
     
      
      Serial.flush();

      Serial.println(stepCount, 2);
      Serial.println("+currrent speed is :");
      Serial.println(stepper.encoder.getSpeed());
      Serial.println("+current strength is :");
      Serial.println(stepper.encoder.getStrength());
      Serial.println("+current angle moved is:");
      Serial.println(stepper.encoder.getAngleMoved());
    } else if (movement < 0) {
      stepper.moveSteps(reverseMovement, CCW, SOFT);
      delay(reverseMovement);
      stepCountAngle = stepper.encoder.getAngleMoved();
      stepCount = stepCountAngle * y;
      Serial.println(stepCount, 2);
      delay(2000);
      Serial.flush();
       Serial.println(stepCount, 2);
      Serial.println("+currrent speed is :");
      Serial.println(stepper.encoder.getSpeed());
      Serial.println("+current strength is :");
      Serial.println(stepper.encoder.getStrength());
      Serial.println("+current angle moved is:");
      Serial.println(stepper.encoder.getAngleMoved());
    } else if (movement == 0) {
      stepper.moveSteps(80000, CCW, SOFT);
      Serial.flush();
    }

  
}

//void loop() {
//   //while (!Serial.available());
//  if(flag==true){
// 
//   stepper.moveSteps(20000, CW, SOFT);
//    delay(2000);
//  }else if(flag==false){
//     stepper.moveSteps(20000, CCW, SOFT);
//      delay(2000);
//    }
//}

void haltStepMin() {
  bool motorState = stepper.getMotorState();
  if (motorState = true) {
    stepper.hardStop(SOFT);
  }
 
  delay(1000);
  stepper.moveSteps(800, CW, SOFT);//400 step back
  delay(1000);
   stepper.encoder.setHome();
  stepper.encoder.angle=0;
  stepper.encoder.angleMoved=0;
      Serial.println("0currrent speed is :");
      Serial.println(stepper.encoder.getSpeed());
      Serial.println("0current strength is :");
      Serial.println(stepper.encoder.getStrength());
      Serial.println("0current angle moved is:");
      Serial.println(stepper.encoder.getAngleMoved());
    
//      if(flag==true){
//        flag=false;
//      }else{
//         flag=true;
//      }
}
