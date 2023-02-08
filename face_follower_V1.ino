/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include the Wire library for I2C
#include <Wire.h>
#include <Servo.h>

Servo ServoX;
Servo ServoY;

float prevX = 90;
float prevY = 45;
float fatorIncremento = 1;

const int servoX=10; 
const int servoY=11; 
 
void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);
  Serial.begin(9600);
  ServoX.attach(servoX);
  ServoY.attach(servoY);

  ServoX.write(prevX);
  ServoY.write(prevY);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);  
} 
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    //char command = Wire.read();
    int command = Wire.read();  
    //Serial.print("comando: ");
    //Simple binnary commands:
    //1--> move servo X right
    //2--> move servo X left
    //3--> move servo Y up
    //4--> move servo Y down
    //5-->stop counting every angle
    
    //If previously angles are not already in the boundaries, keep changing them
    //i.e., if angles are 180, do not increment, if the angles are already zero, do not decrement them also
    if (command == 1 && prevX !=0){
      prevX= prevX - fatorIncremento;
      Serial.println("Right");
    }
    else if (command == 2 && prevX !=180){
      prevX= prevX + fatorIncremento;
      Serial.println("Left");
    }
    else if (command == 3 && prevY !=180){
      prevY = prevY - fatorIncremento/1.5;
      Serial.println("Up");
    }
    else if (command == 4 && prevY !=0){
      prevY = prevY + fatorIncremento;
      Serial.println("Down");
    }
    else{
      // if 5
      Serial.println("BREAK");
      delay(250);
      break;
    }
    ServoX.write(prevX);
    ServoY.write(prevY);
    delay(200);
  }
}
void loop() {
  //delay(100);
}
