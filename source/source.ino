#include <Servo.h>



#include <ezButton.h>
#include <Stepper.h>

ezButton limitSwitchpashe1(7);


const int relay1 = 2;
const int relay2 = 3;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pashe2_counter = 1;
int pos = 0;
int max_pos = 90;

const int IR_LED_PIN = 5;
const int IR_DETECTOR_PIN = 4;
const int IR_DETECTOR_PIN_FEEDER = 7;
const int IR_DETECTOR_PIN_VALID = 8;
const int IR_DETECTOR_PIN_STEPER = 6;
const int stepsPerRevolution = 100;
const int stetupstepsPerRevolution = 1;
Stepper myStepper(stepsPerRevolution, 14, 15, 16, 17);
int start = 1;
int pashe = 0;


void setup_steper()
{
if(digitalRead(IR_DETECTOR_PIN_STEPER) == 1){
  while(digitalRead(IR_DETECTOR_PIN_STEPER) == 1){
    Serial.println("IR STEPER NOT DETEc");
     myStepper.step(stetupstepsPerRevolution);
     delay(50);
    }
  }

  
  while(digitalRead(IR_DETECTOR_PIN_STEPER) == 0){
    Serial.println("IR STEPER NOT DETEc");
     myStepper.step(-stetupstepsPerRevolution);
     delay(50);
    }
    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1) {
    digitalWrite(relay1, LOW);

    while (true) {
      if (IR_DETECTOR_PIN_FEEDER == 0)

          digitalWrite(relay1, HIGH);
        Serial.println("setup IR");
      break;

    }

  }}
void setup() {
  Serial.begin(9600);
  Serial.println("Setup start");
  limitSwitchpashe1.setDebounceTime(100);
  
  myStepper.setSpeed(60);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);



  myservo.attach(9);

  //  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(IR_LED_PIN, OUTPUT);

  digitalWrite(IR_LED_PIN, LOW);


  myservo.write(0);              
  digitalWrite(relay1, HIGH);
  myStepper.setSpeed(60);
setup_steper();

   digitalWrite(relay2, LOW);
        Serial.println("Setup relay 2");
   delay(1000);
  digitalWrite(relay2, HIGH);


  myservo.write(0);              


  pashe = 1;

  



  
Serial.println("Setup end");




}

void loop() {
 
  switch (pashe) {
    case 1:
      pashe1();
      break;

    case 2:
      pashe2();
      break;

    case 3:
      pashe3();
      break;
    case 4:
      pashe4();
      break;
      }

  //  for (pos = 0; pos <= max_pos; pos += 90) { // goes from 0 degrees to 180 degrees
  //    // in steps of 1 degree
  //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(250);                       // waits 15ms for the servo to reach the position
  //  }
  //  for (max_pos = 180; pos >= 0; pos -= 90) { // goes from 180 degrees to 0 degrees
  //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(250);                       // waits 15ms for the servo to reach the position
  //  }

  //
  //  //    Serial.println(pashe);
//  if(digitalRead(IR_DETECTOR_PIN_VALID)== 1){
//    Serial.println("detect");
//    }else{
//      Serial.println(digitalRead(IR_DETECTOR_PIN_VALID));
//      }
//    servo();
}

void servo() {
  myservo.write(30);
  Serial.println("servo 30");
  delay(1000);

  myservo.write(0);
  
  delay(1000);

}
void pashe1() {
  myservo.write(0);
  digitalWrite(relay1, LOW);



  //  delay(700);
  //  digitalWrite(relay1, HIGH);
  //  pashe = 2;


  if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {
    digitalWrite(IR_LED_PIN, HIGH);
    pashe = 2;
    digitalWrite(relay1, HIGH);
    Serial.println("phase 1 object Detect");
  } else {
    digitalWrite(IR_LED_PIN, LOW);
  }

  //  if (limitSwitchpashe1.isPressed()) {
  //    //    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");
  //    Serial.println("pase 1 done move to pase 2");
  //    digitalWrite(relay1, HIGH);
  //    pashe = 2;
  //  }
}

void pashe2() {
  // digitalWrite(IR_LED_PIN, LOW);
  myservo.write(30);
//  delay(100);
  digitalWrite(relay2, LOW);



//  if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {
//    digitalWrite(relay1, LOW);
//    Serial.println("object Detect");
//  } else {
//    Serial.println("object not Detect");
//    digitalWrite(relay1, HIGH);
//  }

  //  delay(2000);
  //  digitalWrite(relay2, HIGH);
  //

  if (digitalRead(IR_DETECTOR_PIN ) == 1 ) {
    digitalWrite(IR_LED_PIN, HIGH);
    Serial.println("phase 2 objec detect");
    pashe = 3;
    pashe2_counter=0;
    digitalWrite(relay2, HIGH);
//    delay(2000);
    Serial.println("object Detect");
  } else {
    digitalWrite(IR_LED_PIN, LOW);
      pashe2_counter +=1;
  Serial.println(pashe2_counter);
  if(pashe2_counter == 600){
    pashe = 1;
    pashe2_counter = 0;
      digitalWrite(relay2, HIGH);
      delay(150);
    }
  }




  //
  //  if (limitSwitchpashe2.isPressed()) {
  //    //    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");
  //    Serial.println("pase 2 done move to pase 3");
  //    digitalWrite(relay2, HIGH);
  //    pashe = 3;
  //  }
}

void pashe3() {


  myStepper.step(stepsPerRevolution);
  myservo.write(0);
  delay(2500);
  myStepper.step(-stepsPerRevolution);
  
  Serial.println("pase 3 done move to pase 4");
  pashe = 4;
}

void pashe4() {
  pashe = 1;
  
  delay(250);
  digitalWrite(relay2, LOW);
  delay(600);
  digitalWrite(relay2, HIGH);
  Serial.println("pase 4 done move to pas 1");
}
