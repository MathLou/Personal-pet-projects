/*For this project, you will need 8 sg90 micro servo motors only
A couble of jumpers, 3D printed pieces, and a custom sield for servo conections, which uou can DIY using a PCB board
This project requires energy, i built a 5 volt DC power supply with and old ATX from a old computer - be carefull cause it has a lot of amps.
Enjoy*/

#include <Servo.h>
#include <math.h>
#include<Wire.h>

Servo bethaServo1;
Servo gamaServo1;
Servo bethaServo2;
Servo gamaServo2;
Servo bethaServo3;
Servo gamaServo3;
Servo bethaServo4;
Servo gamaServo4;

const int bethaPin1 = 13;
const int gamaPin1 = 12;
const int bethaPin2 = 11;
const int gamaPin2 = 10;
const int bethaPin3 = 9;
const int gamaPin3 = 8;
const int bethaPin4 = 7;
const int gamaPin4 = 6;
const int x_input = A0;
const int y_input = A1;

//servo arguments
double betha, gama;
// index 0:betha angles; index 1: gama angles
double computedAngles[2];
// index 0 to 3, legs 1,2,3,4 respectively
float legHeight[4];
//linkage length(in mm)
const int L = 40;
//coordinates input
double x,y;
//radius size: max 24 mm, recomended 22, optimal 22/2;22/3
int rad = 22/2;
//62 to 39
int initialHeight = 62;
//MPU
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;

//current angle from the robot
double angle;
//body of the robot
float bodyLength = 51.98;

//debug functions
void legAdjust();
float coordinatesCompute(float X, float Y);
void servoWriter();
//how fast you want to test the servos? recomended:100 to 25-30(optimal for trotting)
const int speedTest = 15;

void setup() {
  Serial.begin(9600);
  //servos (A first then B)
  bethaServo1.attach(bethaPin1, 544,2400);
  gamaServo1.attach(gamaPin1,544,2400); 
  bethaServo2.attach(bethaPin2,544,2400);
  gamaServo2.attach(gamaPin2,544,2400);
  bethaServo3.attach(bethaPin3,544,2400);
  gamaServo3.attach(gamaPin3,544,2400);
  bethaServo4.attach(bethaPin4,544,2400);
  gamaServo4.attach(gamaPin4,544,2400);
  //coordinates pin
  pinMode(x_input, INPUT);
  pinMode(y_input, INPUT);
  delay(250);
  legAdjust();
  delay(5000);
  //home coords
  coordinatesCompute(0,62);
  servoWriter();
  delay(2000);
}
void loop() {
 
  //debug functions
  //legAdjust();
  //delay(5000);
  //allTester();
  //upAndDown(); 
  //suddenJump();
  //jump();
  //dorsoMoving();
  //dorsoMoving();
  //joystick(); 
  //servoWriter();
  //semiCircleDraw();
  //servoWriter();
  
  for(int i=0;i<10;i++){
    warmingUp();
  } 
  for(int i =0;i<10;i++){
    trot();    
  }
  //crawl(); --> not recommended
  //stretch();
}
float coordinatesCompute(float X, float Y){
  //inverse kinematics equations
  gama = acos((X*X+Y*Y-2*L*L)/(2*L*L));
  betha = atan(Y/X)-atan(sin(gama)/(1+cos(gama)));
  computedAngles[0] = betha*180.0/PI;
  computedAngles[1] = gama*180.0/PI;  
}
void semiCircleDraw(){
  //semi-circle drawing
  //forward move
  for (int x = 2*rad; x>=0;x=x-2){
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
  }
}
void allTester(){
  for (int x = 0; x<=180;x++){
    bethaServo1.write(x);
    bethaServo2.write(x);
    bethaServo3.write(x);
    bethaServo4.write(x);
    gamaServo1.write(x);
    gamaServo2.write(x);
    gamaServo3.write(x);
    gamaServo4.write(x);
    delay(speedTest);
  }  
}
void servoWriter(){
  //debug
  //computedAngles[0]= 90;
  //computedAngles[1]= 0;
  bethaServo1.write(computedAngles[0]);
  bethaServo2.write(computedAngles[0]);
  bethaServo3.write(180-computedAngles[0]);
  bethaServo4.write(180-computedAngles[0]);
  gamaServo1.write(computedAngles[1]);
  gamaServo2.write(computedAngles[1]);
  gamaServo3.write(180-computedAngles[1]);
  gamaServo4.write(180-computedAngles[1]);
  delay(speedTest);  
}
void legAdjust(){
  //debug hardware module
 //1 to 2 side
  //put leg on 90 degrees
  bethaServo1.write(90);
  bethaServo2.write(90);
  //put leg on 0 degrees
  gamaServo1.write(0);
  gamaServo2.write(0);
//3 to 4 side
  //put leg on 90 degress
  bethaServo3.write(90);
  bethaServo4.write(90);
  //put leg on 0 degress
  gamaServo3.write(180);
  gamaServo4.write(180);
}
void jump(){
  for(int i=39; i<=62;i=i+23){
    coordinatesCompute(rad,i);
    servoWriter(); 
    delay(speedTest);
    }  
}
void upAndDown(){
    for(int i=39; i<=62;i++){
    coordinatesCompute(rad,i);
    servoWriter(); 
    delay(speedTest);
    } 
    for(int i=62; i>=39;i--){
    coordinatesCompute(rad,i);
    servoWriter(); 
    delay(speedTest);
    }
}
void suddenJump(){
  for(int i=39; i<=62;i=i+23){
    coordinatesCompute(rad,i);
    servoWriter(); 
    delay(speedTest);
    } 
    for(int i=62; i>=39;i=i-23){
    coordinatesCompute(rad,i);
    servoWriter(); 
    }
    delay(2000);
}
void dorsoMoving(){  
  //dorso moving
  for (int x = 0; x<=2*rad;x=x+1){
    coordinatesCompute(x,initialHeight);
    servoWriter();
  }  
  for (int x = 2*rad; x>=0;x=x-1){
    coordinatesCompute(x,initialHeight);
    servoWriter();
  }  
}
void trot(){
  //leg 1 and leg 3 doing dorso moving, 2 and 4 semi circle
  //step recomended 2
  int step=2;
  for (int x = 0; x<=2*rad;x=x+step){
    //leg 1 and 3    
    transEquilibrium(1); 
    coordinatesCompute(x,legHeight[0]);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]);
     coordinatesCompute(x,legHeight[2]);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);
    //leg 2 and leg 4
    //semi circle formula
    y = -sqrt(rad*rad-(2*rad-x-rad)*(2*rad-x-rad))+initialHeight;
    coordinatesCompute(2*rad-x,y);
    bethaServo2.write(computedAngles[0]);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo2.write(computedAngles[1]);
    gamaServo4.write(180-computedAngles[1]);    
    delay(speedTest);
  }
  //leg 2 and leg 4 doing dorso moving, 1 and 3 semi circle
  for (int x = 0; x<=2*rad;x=x+step){
    //leg 2 and 4  
    transEquilibrium(0);
    coordinatesCompute(x,legHeight[1]);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]);
    coordinatesCompute(x,legHeight[3]);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]);
    //leg 1 and leg 3
    //semi circle formula
    y = -sqrt(rad*rad-(2*rad-x-rad)*(2*rad-x-rad))+initialHeight;
    coordinatesCompute(2*rad-x,y);
    bethaServo1.write(computedAngles[0]);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo1.write(computedAngles[1]);
    gamaServo3.write(180-computedAngles[1]);    
    delay(speedTest);
  }   
}
int coordsDebuger(int X, int Y){
  Serial.print("X: ");
  Serial.print(X);
  Serial.print(" Y: ");
  Serial.print(Y);
  Serial.print(" Betha: ");
  Serial.print(computedAngles[0]);
  Serial.print(" Gama: ");
  Serial.println(computedAngles[1]);
}
void joystick(){
  //Coordinates input(mm)
  //bounds: X:(0,44); Y: (39;62);
  //inverted joystick config
  x = map(analogRead(x_input),0, 1023, 44 ,0);
  y = map(analogRead(y_input),0, 1023, 62, 39);
  coordinatesCompute(x,y);
  coordsDebuger(x,y);  
  servoWriter();
}
void crawl(){
  int step =2;
  // 3 legs on the ground at the same time
  //moving all individually then dorso moving
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 1 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]);    
    delay(speedTest);
  }
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 2 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]);    
    delay(speedTest);
  }
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 4 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo4.write(190-computedAngles[0]);
    gamaServo4.write(185-computedAngles[1]);    
    delay(speedTest);
  }
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 3 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo3.write(190-computedAngles[0]);
    gamaServo3.write(185-computedAngles[1]);    
    delay(speedTest);
  }
  for (int x = 2*rad; x>=0;x=x-step){
    //all dorso moving
    coordinatesCompute(2*rad-x,initialHeight);
    servoWriter(); 
    delay(speedTest);
  }
  float leg1,leg2,leg3,leg4;
  //stage 1
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 1 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]);    
    //dorso move: legs 3, 4 and 2 moving 2/3*radius at the same time
    leg2=map(x,2*rad,0,2/3*rad,4/3*rad);
    coordinatesCompute(leg2,initialHeight);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]); 
    leg3=map(x,2*rad,0,4/3*rad,2*rad);     
    coordinatesCompute(leg3,initialHeight);  
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);
    leg4=map(x,2*rad,0,0,2/3*rad);    
    coordinatesCompute(leg4,initialHeight); 
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]); 
    delay(speedTest);
  }
  //stage 2
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 3 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);    
    //dorso move: legs 1, 4 and 2 moving 2/3*radius at the same time
    leg1=map(x,2*rad,0,0,2/3*rad);
    coordinatesCompute(leg1,initialHeight);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]); 
    leg4=map(x,2*rad,0,2/3*rad, 4/3*rad);     
    coordinatesCompute(leg4,initialHeight);  
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]);
    leg2=map(x,2*rad,0,4/3*rad,2*rad);    
    coordinatesCompute(leg2,initialHeight); 
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]); 
    delay(speedTest);
  }
  //stage 3
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 2 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]);    
    //dorso move: legs 3, 4 and 2 moving 2/3*radius at the same time
    leg1=map(x,2*rad,0,2/3*rad,4/3*rad);
    coordinatesCompute(leg1,initialHeight);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]); 
    leg3=map(x,2*rad,0,0,2/3*rad);     
    coordinatesCompute(leg3,initialHeight);  
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);
    leg4=map(x,2*rad,0,4/3*rad,2*rad);    
    coordinatesCompute(leg4,initialHeight); 
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]); 
    delay(speedTest);
  }
  //stage 4
  for (int x = 2*rad; x>=0;x=x-step){
    //leg 4 semi-circle
    y = -sqrt(rad*rad-(x-rad)*(x-rad))+initialHeight;
    coordinatesCompute(x,y);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]);    
    //dorso move: legs 1, 4 and 2 moving 2/3*radius at the same time
    leg1=map(x,2*rad,0,4/3*rad,2*rad);
    coordinatesCompute(leg1,initialHeight);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]); 
    leg3=map(x,2*rad,0,2/3*rad, 4/3*rad);     
    coordinatesCompute(leg3,initialHeight);  
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);
    leg2=map(x,2*rad,0,0,2/3*rad);    
    coordinatesCompute(leg2,initialHeight); 
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]); 
    delay(speedTest);
  }
}
void warmingUp(){
  int speed = 10;
  int step = 2;
  for (int h = initialHeight; h>=45;h=h-step){
    //start MPU balance for 1-3 mode
    transEquilibrium(1);
    //leg 1 and 3    
    coordinatesCompute(rad,legHeight[0]);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]);
    coordinatesCompute(rad,legHeight[2]);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);
    //leg 2 and leg 4
    //lifting legs
    coordinatesCompute(rad,h);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]);    
    delay(speed);
  }
  for (int h = 45; h<=initialHeight;h=h+step){
    //start MPU balance for 1-3 mode
    transEquilibrium(1);
    //leg 1 and 3    
    coordinatesCompute(rad,legHeight[0]);
    bethaServo1.write(computedAngles[0]);
    gamaServo1.write(computedAngles[1]);
    coordinatesCompute(rad,legHeight[2]);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo3.write(180-computedAngles[1]);
    //leg 2 and leg 4
    //returning legs
    coordinatesCompute(rad,h);
    bethaServo2.write(computedAngles[0]);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo2.write(computedAngles[1]);
    gamaServo4.write(180-computedAngles[1]);    
    delay(speed);
  }
  for (int h = initialHeight; h>=45;h=h-step){
     //start balancing with 0 mode
    transEquilibrium(0);
    //leg 2 and leg 4 on the ground
    coordinatesCompute(rad,legHeight[1]);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]);
    coordinatesCompute(rad,legHeight[3]);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]);    
    //lifting leg 1 and leg 3
    coordinatesCompute(rad,h);
    bethaServo1.write(computedAngles[0]);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo1.write(computedAngles[1]);
    gamaServo3.write(180-computedAngles[1]);    
    delay(speed);
  } 
for (int h = 45; h<=initialHeight;h=h+step){
  //start balancing with 0 mode
    transEquilibrium(0);
    //leg 2 and leg 4 on the ground
    coordinatesCompute(rad,legHeight[1]);
    bethaServo2.write(computedAngles[0]);
    gamaServo2.write(computedAngles[1]);
    coordinatesCompute(rad,legHeight[3]);
    bethaServo4.write(180-computedAngles[0]);
    gamaServo4.write(180-computedAngles[1]);     
    //leg 1 and leg 3
    coordinatesCompute(rad,h);
    bethaServo1.write(computedAngles[0]);
    bethaServo3.write(180-computedAngles[0]);
    gamaServo1.write(computedAngles[1]);
    gamaServo3.write(180-computedAngles[1]);    
    delay(speed);
  }      
}
}
