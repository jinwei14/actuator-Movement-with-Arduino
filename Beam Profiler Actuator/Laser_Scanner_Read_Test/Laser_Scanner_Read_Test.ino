#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19


int FAR_PIN = A9;
int NEAR_PIN = A5;
int ALARM_PIN = A10;
int VOLTAGE_PIN = A11;

int farValue;
int nearValue;
int alarmValue;
int voltageValue;

int notAtCentreFar = 0;
int notAtCentreNear = 0;
int dataSent = 0;

int state=0;


float vout = 0.0;
float vin = 0.0;
float R1 = 1000.0; // resistance of R1 (1K)
float R2 = 1000.0; // resistance of R2 (1K)

void step(int stepperPin, int steps, int dirPin, boolean dir) {
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);
  }
}

void moveToCentreFromFar() {
  //Serial.write(4);
  step(Z_STEP_PIN, 100, Z_DIR_PIN, true);
  notAtCentreFar = 0;
}

void moveToCentreFromNear() {
  //Serial.write(4);
  step(Z_STEP_PIN, 100, Z_DIR_PIN, false);
  notAtCentreNear = 0;
}

void setup() {

 pinMode(X_STEP_PIN, OUTPUT);
 pinMode(X_DIR_PIN, OUTPUT);
 pinMode(X_ENABLE_PIN, OUTPUT);
 pinMode(X_MIN_PIN, INPUT_PULLUP);
 pinMode(X_MIN_PIN, INPUT_PULLUP);

 pinMode(Y_STEP_PIN, OUTPUT);
 pinMode(Y_DIR_PIN, OUTPUT);
 pinMode(Y_ENABLE_PIN, OUTPUT);
 pinMode(Y_MAX_PIN, INPUT_PULLUP);
 pinMode(Y_MIN_PIN, INPUT_PULLUP);

 pinMode(Z_STEP_PIN, OUTPUT);
 pinMode(Z_DIR_PIN, OUTPUT);
 pinMode(Z_ENABLE_PIN, OUTPUT);
 pinMode(Z_MAX_PIN, INPUT_PULLUP);
 pinMode(Z_MIN_PIN, INPUT_PULLUP);

 pinMode(NEAR_PIN, INPUT);
 pinMode(FAR_PIN, INPUT);
 pinMode(ALARM_PIN, INPUT);
 pinMode(VOLTAGE_PIN, INPUT);

  Serial.begin(9600);
}



void loop() {
  farValue = analogRead(FAR_PIN);
  nearValue = analogRead(NEAR_PIN);
  alarmValue = analogRead(ALARM_PIN);
  voltageValue = analogRead(VOLTAGE_PIN);

  float voltage = voltageValue * (5 / 1023.0);
  vin = voltage / (R2/(R1+R2)); 

  if (Serial.available() > 0)
  {
    state = Serial.read(); // used to read incoming data
    
    switch(state)// see what was sent to the board
    {
      case '7': //Moves along the sample towers
      if (farValue < 10 && nearValue < 10) {
      Serial.flush();
      Serial.println(vin, 4);
      delay(500);
      step(X_STEP_PIN, 200, X_DIR_PIN, true);
      delay(500);
      Serial.flush();
    }
    while (farValue > 10) {
      Serial.println("Far");
      farValue = analogRead(FAR_PIN);
      moveToCentreFromFar();
      Serial.flush();
      delay(100);
    }
    while (nearValue > 10) {
      Serial.println("Near");
      farValue = analogRead(NEAR_PIN);
      moveToCentreFromNear();
      Serial.flush();
      delay(100);
    }
      break;
      case '8':
      step(X_STEP_PIN, 2000, X_DIR_PIN, false);
      step(Y_STEP_PIN, 200, Y_DIR_PIN, true);
      break;
      case '9':
      step(X_STEP_PIN, 200, X_DIR_PIN, true);
      step(Y_STEP_PIN, 600, Y_DIR_PIN, false);
      break;
      default:
      break;
    }
  }
  
//  if (notAtCentreNear == 1){
//    moveToCentreFromNear();
//    delay(2000);
//  }
//
//  if (notAtCentreFar == 1){
//    moveToCentreFromFar();
//    delay(2000);
//  }

//    if (farValue < 10 && nearValue < 10) {
//      Serial.write(1);
//      Serial.flush();
//      //delay(500);
//      Serial.println(vin, 4);
//      delay(200);
//      Serial.flush();
//      step(X_STEP_PIN, 200, X_DIR_PIN, true);
//      delay(500);
//    }
      
//    } else if (farValue > 10) {
//      //Serial.write(2);
//      notAtCentreFar = 1;
//      delay(500);
//      
//    } else if (nearValue > 10) {
//      //Serial.write(3);
//      notAtCentreNear = 1;
//      delay(500);
//    }


}


