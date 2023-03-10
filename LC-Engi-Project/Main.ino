//02 05 2021 Ex Number: 108051

#include "BluetoothSerial.h"
#include <Servo.h>

BluetoothSerial SerialBT;
Servo servo;

//Autonomus
const int Auto = 2;
int reading;

//Extender
const int M3 = 14; //M variables control direction 
const int E3 = 12; //E variables control speed

//BT Commands 
String message = "";

//Drive Train
const int M2 = 16;
const int E2 = 17;
const int M1 = 18;
const int E1 = 19;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("108051 Engi Project"); //Device Name

  pinMode(Auto, INPUT);
  
  pinMode(M3, OUTPUT);
  pinMode(E3, OUTPUT);
  
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
  
  servo.attach(15);
  servo.write(0);
}

void loop() {
  reading = digitalRead(Auto);
  if (reading == HIGH){                  
    //This section is the automatic routine
    SerialBT.println("Automatic Begin");
    delay(2000);
    forward();
    delay(4000);
    halt();
    delay(200);
    left();
    delay(2000);
    halt();
    delay(200);
    back();
    delay(3000);
    halt();
    delay(200);
    extend();
    delay(250);
    servo.write(90);
    delay(1000);
    retract();
    delay(250);
    servo.write(0);
  }

  if (SerialBT.available()) {             
    //This section is Bluetooth Control
    char incomingChar = SerialBT.read();

    if (incomingChar!= '\n'){
        message += String(incomingChar);
      }
      else{
        message = "";
      }
      Serial.write(incomingChar);

    if (message == "ext"){
      extend();
    }
    else if (message == "ret"){
      retract();
    }
    else if (message == "up"){
      servo.write(90);
    }
    else if (message == "down"){
      servo.write(0);
    }
    else if (message == "f"){
      forward();
    }
    else if (message == "b"){
      back();
    }
    else if (message == "r"){
      right();
    }
    else if (message == "l"){
      left();
    }
    else if (message == "s"){
      halt();
    }
    delay(20);
  }
}

//Functions
void extend() {
      digitalWrite(M3, LOW);
      digitalWrite(E3, HIGH); 
      delay(575);
      digitalWrite(E3, LOW);
}
void retract() {
      digitalWrite(M3, HIGH);
      digitalWrite(E3, HIGH); 
      delay(600);
      digitalWrite(E3, LOW);
}
void forward() {
      digitalWrite(E1, HIGH); 
      digitalWrite(M1, HIGH); 
      digitalWrite(E2, HIGH); 
      digitalWrite(M2, LOW); 
}
void back() {
      digitalWrite(E1, HIGH); 
      digitalWrite(M1, LOW); 
      digitalWrite(E2, HIGH); 
      digitalWrite(M2, HIGH); 
}
void right() {
      digitalWrite(E1, HIGH); 
      digitalWrite(M1, HIGH); 
      digitalWrite(E2, HIGH); 
      digitalWrite(M2, HIGH);
}
void left() {
      digitalWrite(E1, HIGH); 
      digitalWrite(M1, LOW); 
      digitalWrite(E2, HIGH); 
      digitalWrite(M2, LOW); 
}
void halt() {
      digitalWrite(E1, LOW); 
      digitalWrite(M1, LOW); 
      digitalWrite(E2, LOW); 
      digitalWrite(M2, LOW); 
}
