#include <Servo.h>



#include <ezButton.h>
#include <Stepper.h>

//ezButton limitSwitchpashe1(7);


int delay_after_step = 150;
int delay_feeder = 180;
bool status_servo = true;
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
const int brake_relay = 4;
int p2_status = 0;
const int IR_DETECTOR_PIN_VALID = 8;
const int IR_DETECTOR_PIN_FEEDER = 7;
const int IR_DETECTOR_PIN_STEPER = 6;
const int IR_DETECTOR_PIN = 5;

int servo_up = 18;
int servo_down = 0;
const int servo = 9;
Servo myservo;
int err = 0;
const int stepsPerRevolution = 100;
const int stetupstepsPerRevolution = 1;
Stepper myStepper(stepsPerRevolution, 14, 15, 16, 17);

// twelve servo objects can be created on most boards
int pashe2_counter = 1;
int pashe2_counter_0 = 1;
bool pashe2_counter_0_status = true;
int pos = 0;
int max_pos = 90;

//const int IR_LED_PIN = 5;

int start = 1;
int pashe = 0;

void setup_feeder() {
  relay_1_on();
  while (true) {

    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {
      //      delay(100);
      //      relay_1_off();
      //      pashe = 15;
      break;
    }
  }
  delay(100);
  while (true) {

    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 0 ) {
      delay(delay_feeder);
      relay_1_off();
      pashe = 15;
      break;
    }
  }
  delay(100);


  while (true) {

    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 0 ) {
      relay_1_on();
      delay(22);
      relay_1_off();
      delay(150);

    } else {
      relay_1_on();
      delay(10);
      relay_1_off();
      break;
    }
  }

}

void testing_sensor_feeder() {
  relay_1_on();
  Serial.println("start looking for feeder detect");
  while (true) {
    if (digitalRead(IR_DETECTOR_PIN_FEEDER) == 1) {
      Serial.println("feeder detect");
      relay_1_off();

      delay(1000);
      break;
    } else {
      Serial.print("feeder detect");
      Serial.println(digitalRead(IR_DETECTOR_PIN_FEEDER));
    }
  }


  Serial.println("start looking for feeder setup");

  relay_1_on();
  while (true) {
    if (digitalRead(IR_DETECTOR_PIN_FEEDER) == 0) {
      Serial.println("feeder setup detect");
      relay_1_off();
      delay(1000);
      break;
    } else {
      Serial.print("feeder setup");
      Serial.println(digitalRead(IR_DETECTOR_PIN_FEEDER));
    }

  }







}

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


void brake_motor_2() {
  relay_2_off();
  digitalWrite(brake_relay, LOW);
  delay(500);
  digitalWrite(brake_relay, HIGH);




}





void setup_steper()
{

  if (digitalRead(IR_DETECTOR_PIN_STEPER) == 1) {
    while (digitalRead(IR_DETECTOR_PIN_STEPER) == 1) {
      //      Serial.println("IR STEPER DETEc");
      myStepper.step(stetupstepsPerRevolution);
      delay(50);
    }
  }


  while (digitalRead(IR_DETECTOR_PIN_STEPER) == 0) {
    //    Serial.println("IR STEPER NOT DETEc");
    myStepper.step(-stetupstepsPerRevolution);
    delay(50);
  }
  //
  Serial.println("start setup feeder 1");
  delay(150);

  setup_feeder();
  
  delay(150);
  relay_2_on();
  Serial.println("Setup relay 2");
  delay(2000);
  relay_2_off();

}


void test_relay() {

  while (1) {
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
  pinMode(brake_relay, OUTPUT);
  digitalWrite(brake_relay, HIGH);
  relay_1_off();
  relay_2_off();





  //  relay_1_on();
  //  test_relay();
  Serial.println("Setup start");
  myservo.attach(servo);

  myservo.write(0);
  myStepper.setSpeed(60);
//  setup_steper();


  pashe = 0;
  Serial.println("Setup end");
}

void loop() {


//  setup_feeder();

//  delay(1000);
  //  Serial.println(digitalRead(IR_DETECTOR_PIN_FEEDER));


  myStepper.step(stepsPerRevolution);
  delay(2500);
  myStepper.step(-stepsPerRevolution);
  delay(2500);

//    switch (pashe) {
//      case 0:
//        pashe0();
//        break;
//      case 1:
//        pashe1();
//        break;
//      case 15:
//        pashe1_5();
//        break;
//  
//      case 2:
//        pashe2();
//        break;
//  
//      case 3:
//        pashe3();
//        break;
//      case 4:
//        pashe4();
//        break;
//    }


  //  testing_sensor_feeder();


  //
  //            myStepper.step(stepsPerRevolution);
  //    delay(2500);
  //    myStepper.step(-stepsPerRevolution);
  //    delay(2500);
  //      if (digitalRead(IR_DETECTOR_PIN_VALID) == 1) {
  //        Serial.println("valid 1");
  //      } else {
  //        Serial.println("0");
  //      }
  //      //
  //      if (digitalRead(IR_DETECTOR_PIN_STEPER) == 1) {
  //        Serial.println("steper 1");
  //      } else {
  //        Serial.println("0");
  //      }
  //
  //      if (digitalRead(IR_DETECTOR_PIN_FEEDER) == 1) {
  //        Serial.println("feeder 1");
  //      } else {
  //        Serial.println("0");
  //      }
  //      if (digitalRead(IR_DETECTOR_PIN) == 1) {
  //        Serial.println("detector 1");
  //      } else {
  //        Serial.println("0");
  //      }
  //  //test_relay();
  //
  //    delay(200);
  //
  //    servo();
  //  servo1();
  //  myservo.write(0);

}

void servo1() {
  myservo.write(90);
  Serial.println("servo 30");
  delay(1000);

  myservo.write(0);
  Serial.println("servo 0");
  delay(1000);

}
void pashe0() {
  relay_1_off();
  relay_2_off();
  digitalWrite(brake_relay, HIGH);
  myservo.write(0);
  pashe = 1;
  p2_status = 0;
  delay(200);
}
void pashe1() {

  setup_feeder();
  pashe = 2;
//  relay_1_on();
//
//
//
//  //  delay(700);
//  //  digitalWrite(relay1, HIGH);
//  //  pashe = 2;
//
//  while (true) {
//
//    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {
//      //      delay(100);
//      //      relay_1_off();
//      //      pashe = 15;
//      break;
//    }
//  }
//  delay(100);
//  //    relay_1_on();
//  while (true) {
//
//    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 0 ) {
//      delay(delay_feeder);
//      relay_1_off();
//      pashe = 2;
//      break;
//    }
//  }
//
//  //
//  // relay_1_on();
//  //  while (true) {
//  //
//  //    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 0 ) {
//  ////      delay(270);
//  //      relay_1_off();
//  //      pashe = 15;
//  //      break;
//  //    }
//  //  }
//
//
//
//
//  //  if (limitSwitchpashe1.isPressed()) {
//  //    //    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");
//  //    Serial.println("pase 1 done move to pase 2");
//  //    digitalWrite(relay1, HIGH);
//  //    pashe = 2;
//  //  }
}

void pashe1_5() {
  //  while (true) {
  //    if (digitalRead(IR_DETECTOR_PIN_FEEDER ) == 1 ) {
  //      relay_1_on();
  //    } else {
  //      if (p2_status == 0) {
  //        delay(delay_feeder);
  //        p2_status = 1;
  //      }
  //      relay_1_off();
  //      break;
  //      //    Serial.println("object not Detect");
  //    }
  //  }
  delay(3000);
  pashe = 1;


}
void pashe2() {
  //  Serial.println(pashe2_counter_0_status);




  // digitalWrite(IR_LED_PIN, LOW);

  if (status_servo == true) {

    myservo.write(90);
  }
  delay(100);

  relay_2_on();








  //  delay(2000);
  //  digitalWrite(relay2, HIGH);
  //



  //
  if (pashe2_counter_0_status == true) {

    while (true) {
      if (digitalRead(IR_DETECTOR_PIN_VALID) == 0) {
        pashe2_counter_0 += 1;
        Serial.println(pashe2_counter_0);
        if (pashe2_counter_0 == 200) {

//          relay_1_on();
//          delay(20);
//          relay_1_off();
          pashe2_counter_0_status = false;
          Serial.println(String(pashe2_counter_0_status));
          break;
        }
      } else {
        Serial.println(String(pashe2_counter_0_status));
        pashe2_counter_0_status = false;
        break;
      }

    }
    Serial.println("doneasd");
    pashe2_counter_0 = 0;
  }


  while (true) {
    if (digitalRead(IR_DETECTOR_PIN ) == 1 ) {

      Serial.println("phase 2 objec detect");
      pashe = 3;
      pashe2_counter = 0;
      brake_motor_2();
      relay_2_off();
      digitalWrite(brake_relay, LOW);
      break;
    } else {
      //    digitalWrite(IR_LED_PIN, LOW);
      pashe2_counter += 1;
      Serial.println(pashe2_counter);
      if (pashe2_counter == 600) {
        pashe = 0;
        pashe2_counter = 0;
        relay_2_off();
        relay_1_off();
        delay(150);
        break;
      }
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
  myservo.write(0);
  myStepper.step(stepsPerRevolution);
  delay(2500);
  myStepper.step(-stepsPerRevolution);
  digitalWrite(brake_relay, HIGH);
  Serial.println("pase 3 done move to pase 4");

  pashe = 4;
}

void pashe4() {
  pashe2_counter_0_status = true;
  digitalWrite(brake_relay, HIGH);

  myservo.write(0);
  delay(250);
  if (digitalRead(IR_DETECTOR_PIN_VALID) == 1) {

    relay_2_on();
    delay(1400);
    relay_2_off();
  } else {
    relay_2_on();
    delay(600);
    relay_2_off();
    //    while (true) {
    //      if (digitalRead(IR_DETECTOR_PIN ) == 0 ) {
    //        delay(150);
    //        relay_2_off();
    //        break;
    //      }
    //    }



  }

  pashe = 0;


  Serial.println("pase 4 done move to pas 1");
}
