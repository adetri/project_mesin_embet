#include <Servo.h>



#include <ezButton.h>
#include <Stepper.h>

//ezButton limitSwitchpashe1(7);






//int pwmA = 10;
//int pwmB = 11;
//int enA = 12;
//int enB = 13;
//int buz = 4;
//const int max_power = 255;
//const int stop_power = 0;
//const int setup_power = 135;

const int relay_1 = 10;
const int relay_2 = 11;

const int IR_DETECTOR_PIN_VALID = 8;
const int IR_DETECTOR_PIN_FEEDER = 7;
const int IR_DETECTOR_PIN_STEPER = 6;
const int IR_DETECTOR_PIN = 5;

const int servo = 9;
Servo myservo;

const int stepsPerRevolution = 100;
const int stetupstepsPerRevolution = 1;
Stepper myStepper(stepsPerRevolution, 14, 15, 16, 17);

// twelve servo objects can be created on most boards
int pashe2_counter = 1;
int pos = 0;
int max_pos = 90;

//const int IR_LED_PIN = 5;

int start = 1;
int pashe = 0;


void relay_1_off()
{
  digitalWrite(relay_1, HIGH);
//  Serial.println("relay 1 off");
}

void relay_1_on()
{
  digitalWrite(relay_1, LOW);
//  Serial.println("relay 1 on");
}

void relay_2_off()
{
  digitalWrite(relay_2, HIGH);
//  Serial.println("relay 2 off");
}

void relay_2_on()
{
  digitalWrite(relay_2, LOW);
//  Serial.println("relay 2 on");
}






void setup_steper()
{

  if (digitalRead(IR_DETECTOR_PIN_STEPER) == 1) {
    while (digitalRead(IR_DETECTOR_PIN_STEPER) == 1) {
      Serial.println("IR STEPER DETEc");
      myStepper.step(stetupstepsPerRevolution);
      delay(50);
    }
  }


  while (digitalRead(IR_DETECTOR_PIN_STEPER) == 0) {
    Serial.println("IR STEPER NOT DETEc");
    myStepper.step(-stetupstepsPerRevolution);
    delay(50);
  }
  //
  delay(150);
  if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1) {
    //    digitalWrite(relay1, LOW);
    relay_1_on();
    Serial.println("setup IR start");



    while (true) {
      if (digitalRead(IR_DETECTOR_PIN_FEEDER )== 0) {
        relay_1_off();
        break;
      }


    }


  }
  delay(150);
  relay_2_on();
  Serial.println("Setup relay 2");
  delay(1000);
  relay_2_off();

}


void test_relay(){

  while(1){
  relay_1_on();
    delay(1000);
  relay_1_off();
  delay(1000);
  relay_2_on();
    delay(1000);
  relay_2_off();
    delay(1000);
  }
  }


void setup() {



  Serial.begin(9600);

  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  relay_1_off();
  relay_2_off();


//  relay_1_on();
//  test_relay();
  Serial.println("Setup start");
  myservo.attach(servo);

  myservo.write(0);
  myStepper.setSpeed(60);
    setup_steper();



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

  
//  
//            myStepper.step(stepsPerRevolution);
//    delay(2500);
//    myStepper.step(-stepsPerRevolution);
//    delay(2500);
//    if (digitalRead(IR_DETECTOR_PIN_VALID) == 1) {
//      Serial.println("valid 1");
//    } else {
//      Serial.println("0");
//    }
//    //
//    if (digitalRead(IR_DETECTOR_PIN_STEPER) == 1) {
//      Serial.println("steper 1");
//    } else {
//      Serial.println("0");
//    }
//  
//    if (digitalRead(IR_DETECTOR_PIN_FEEDER) == 1) {
//      Serial.println("feeder 1");
//    } else {
//      Serial.println("0");
//    }
//    if (digitalRead(IR_DETECTOR_PIN) == 1) {
//      Serial.println("detector 1");
//    } else {
//      Serial.println("0");
//    }
//test_relay();

  //  delay(200);

  //    servo();
}

void servo1() {
  myservo.write(30);
  Serial.println("servo 30");
  delay(1000);

  myservo.write(0);

  delay(1000);

}
void pashe1() {
  myservo.write(0);
  relay_1_on();



  //  delay(700);
  //  digitalWrite(relay1, HIGH);
  //  pashe = 2;


  if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {
    relay_1_off();
    pashe = 2;
    Serial.println("phase 1 object Detect");
  } else {
    //    digitalWrite(IR_LED_PIN, LOW);'
     Serial.println("phase 1 object not  Detect"); 
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
  relay_2_on();



  if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {

    relay_1_on();
    Serial.println("object Detect");
  } else {
    relay_1_off();
//    Serial.println("object not Detect");

  }

  //  delay(2000);
  //  digitalWrite(relay2, HIGH);
  //

  if (digitalRead(IR_DETECTOR_PIN ) == 1 ) {

    Serial.println("phase 2 objec detect");
    pashe = 3;
    pashe2_counter = 0;
    relay_2_off();

  } else {
    //    digitalWrite(IR_LED_PIN, LOW);
    pashe2_counter += 1;
      Serial.println(pashe2_counter);
    if (pashe2_counter == 600) {
      pashe = 1;
      pashe2_counter = 0;
      relay_2_off();
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
  delay(2500);
  myStepper.step(-stepsPerRevolution);
  Serial.println("pase 3 done move to pase 4");
  pashe = 4;
}

void pashe4() {
  pashe = 1;

  delay(250);
  relay_2_on();
  delay(600);
  relay_2_off();
  Serial.println("pase 4 done move to pas 1");
}
