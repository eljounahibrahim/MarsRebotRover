
#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN0  100
#define SERVOMAX0  500

#define SERVOMIN3  150 
#define SERVOMAX3  450 

#define SERVOMIN1  200 
#define SERVOMAX1  400


#define SERVOMIN4  90 
#define SERVOMAX4  700



PS2X ps2x;
int PS2 = 0; 
#define LF 46 //left forward
#define LB 42 //left backward
#define RF 44 //right forward
#define RB 40 //right backward

int   angle0=300;
int   angle2=200;
int   angle3=200;

int inc =1;

void roverForward(){
  digitalWrite(RB,LOW);
  digitalWrite(LB,LOW);
  delay(50);
  digitalWrite(RF,HIGH);
  digitalWrite(LF,HIGH);
  
}

void roverBackward(){
  
  digitalWrite(RF,LOW);
  digitalWrite(LF,LOW);
  delay(50);
  digitalWrite(RB,HIGH);
  digitalWrite(LB,HIGH);
}
void roverLeft(){
  
  digitalWrite(RB,LOW);
  digitalWrite(LF,LOW);
  
  delay(50);
  digitalWrite(LB,HIGH);
  digitalWrite(RF,HIGH);
  
  }
  void roverRelease(){
  digitalWrite(RF,LOW);
   digitalWrite(LB,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LF,LOW);
}
void roverRight(){
  digitalWrite(RF,LOW);
   digitalWrite(LB,LOW);
   
   delay(50);
  digitalWrite(RB,HIGH);
  digitalWrite(LF,HIGH);
 
}
void roverStop(){
  digitalWrite(RF,LOW);
   digitalWrite(LB,LOW);
 
  digitalWrite(RB,LOW);
  digitalWrite(LF,LOW);
 
}

//PSX CONTROLLER CONFIGURATION
#define DATA 12
#define CLK 13
#define CMD 11
#define CS 10

void setup(){
 PS2 = ps2x.config_gamepad(CLK,CMD,CS,DATA, true, true);  
  pinMode (RF, OUTPUT);
  pinMode (RB, OUTPUT);
  pinMode (LF, OUTPUT);
  pinMode (LB, OUTPUT);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60); 
  delay(10);
}



void loop(){
ps2x.read_gamepad();//read incoming commands



if(ps2x.Button(PSB_PAD_UP)) {
     roverForward();
    }
    
 if(ps2x.Button(PSB_PAD_DOWN)) {
      
      roverBackward();
    }
 if(ps2x.Button(PSB_PAD_RIGHT)) {
     
      roverRight();
    }
    if(ps2x.Button(PSB_PAD_LEFT)) {
      
      roverLeft();
    }
    if(ps2x.Button(PSB_PAD_RIGHT)==0 && ps2x.Button(PSB_PAD_DOWN)==0&& ps2x.Button(PSB_PAD_UP)==0 && ps2x.Button(PSB_PAD_LEFT)==0){
     
      roverStop();
      }






   if(ps2x.Button(PSB_CIRCLE) && angle0<SERVOMAX0)//BASE
   {
   
      angle0=angle0+inc;
      pwm.setPWM(0,0,angle0);  
     
    }
else if (ps2x.Button(PSB_SQUARE)&& angle0>SERVOMIN0) {
      angle0=angle0-inc;
      
      pwm.setPWM(0,0,angle0);    
      
    }



 if(ps2x.Button(PSB_R1) && angle3<SERVOMAX3) {//effector
      angle3=angle3+inc;
   
      pwm.setPWM(3,0,angle3);
  
    }
else if(ps2x.Button(PSB_R2)&& angle3>SERVOMIN3) {
      angle3=angle3-inc;
  
      pwm.setPWM(3,0,angle3);  
     
    }  
    


if(ps2x.Button(PSB_TRIANGLE) && angle2>SERVOMIN1 ) {//up and down
      angle2=angle2-inc;
      //Serial.println(angle2);
      pwm.setPWM(2,0,angle2);
}
else if (ps2x.Button(PSB_CROSS)&& angle2<SERVOMAX1 ) {
      angle2=angle2+inc;
      //Serial.println(angle2);
      pwm.setPWM(2,0,angle2);
}

} 
