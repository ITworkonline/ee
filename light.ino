#include <Servo.h>
Servo servo;
int a = A3; // what pin on the arduino is the OUT pin connected to
int servoPin = 3;
int val=0;
 void setup(){
  pinMode(A3, OUTPUT);
  //digitalWrite(servopin,LOW);
  Serial.begin(9600);
  Serial.println("Sparkfun TEMT6000 Module Example Sketch | cactus.io");
  servo.attach(servoPin);
  }

  void loop(){
  val = analogRead(a);
  Serial.println(val);
  detectlight();
  
  delay(2000);
  }
  
  
  
  void detectlight()
  {
  
  if(val >= 4)
    {
      servo.write(50);
      Serial.println("open");
      
      
      }
  else 
  {
   servo.write(200);
    Serial.println("close");
  
    }
  }
