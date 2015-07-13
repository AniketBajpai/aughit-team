#define TRIGGER_PIN   6 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200
#define LEDPin 13 // Onboard LED
#include<Servo.h>
#include <NewPing.h>
int prev=0 ;
Servo myservo ;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int rotation=0  ;
long distance=0; 
long distance_moved=0;long distance1=0;
String integer ="";int inChar;int s;
int value = 0;
int sign = 1;
void setup() {
 Serial.begin (9600);

 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 myservo.attach(9);
 //Serial.println(distance1);
 //Serial.println(distance_moved);
 //Serial.println(distance);

}
unsigned int uS ;
void loop() {   
  
 while (Serial.available()){
     
    char ch = Serial.read();
    if(ch >= '0' && ch <= '9') // is this an ascii digit between 0 and 9?
       value = (value * 10) + (ch - '0'); //  accumulate the value
    else if( ch == '-')
      { sign = -1; 
    }
    else // this assumes any char not a digit or minus sign terminates the value
    {
       value = value * sign ;  // set value to the accumulated value
       //Serial.println(value);
        distance_moved=value ;
        value=0 ;  // reset value to 0 ready for the next sequence of digits
        sign = 1;
        char y =Serial.read(); char x = Serial.read(); char z = Serial.read();
        rotation =(y-'0')*100 + (x-'0')*10 + z-'0' ;
      // Serial.println("last");
    }
     p2: ;
     uS = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
     //Serial.print("Ping: ");
     //Serial.println(uS );
     //Serial.println("end of serial.available");
     distance1=uS  ;
     if(distance1<=6)
     {goto p2 ;
     }
   
   
 
}  
   p3: ;
   uS = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
    if(uS<=6)
    { goto p3 ;
    }
 // Serial.print("Ping: ");
 // Serial.println(uS );
  prev=distance ;
  distance=uS  ;
  
  Serial.println(distance_moved); 
 Serial.println(distance1);
 Serial.println(distance);
 
if (distance_moved>0) {                          //move right
 if((distance1-distance_moved) < distance) {
   if(prev<distance)
    { goto g2 ;
    }
   
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
     
      }
  else {  g2: ;
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);  } 
  
}

if (distance_moved<0){                          //move left                      
 if((distance1-distance_moved) > distance) 
 {  if(prev>distance)
    { goto g1 ;
    }
    //Serial.println("if");
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);  
      
   }
else { // Serial.println("else");
       g1: ;
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);    } 
}
  myservo.write(rotation);
//Serial.println(rotation);
}

