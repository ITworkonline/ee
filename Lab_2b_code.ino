byte Micro_Switch = A3;
byte Big_Switch = A1;
byte Out2 = 2;
byte OutA5 = A5;
int times=0;
int n=0;

void setup() {
  pinMode(Micro_Switch, INPUT_PULLUP);
  pinMode(Big_Switch, INPUT_PULLUP);
  pinMode(Out2, OUTPUT);
  pinMode(OutA5, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  Serial.println(times);
  if(times>20 && times<30){
    watch();}
  else if (times>35 && times<45){
  anger();}
  else if (times>60 && times<70){
  loud();}
  else{
  standardmotion();}
  }

void standardmotion(){
    
  bool Big_connect = (digitalRead(Big_Switch) == LOW);
  bool Micro_connect = (digitalRead(Micro_Switch) == LOW);  
  
      if(Big_connect && !Micro_connect){  //switch pressed, micro still no left  
        Serial.println("Stage 1"); 
        digitalWrite(Out2, HIGH);
        digitalWrite(OutA5, LOW);
        times++;        
        //forward 
      }     
      else if(Big_connect && Micro_connect){  //switch pressed, micro swich left 
        Serial.println("Stage 2"); 
        digitalWrite(Out2, HIGH);
        digitalWrite(OutA5, LOW);        
        //forward 
      } else if(!(Big_connect) && Micro_connect){ // switch turned other way, micro switch left
        delay(n);
        Serial.println("Stage 3");
        digitalWrite(Out2, LOW);
        digitalWrite(OutA5, HIGH); 
        //backward
      }  
      else{
        Serial.println(" stop "); 
        digitalWrite(Out2, LOW);
        digitalWrite(OutA5, LOW);

      if(times>70){times=0;}   
      }
  }

void loud(){
    digitalWrite(Out2, LOW);
    digitalWrite(OutA5, HIGH);
    delay(1000);
    digitalWrite(Out2, LOW);
    digitalWrite(OutA5, LOW);
    delay(2000);
    times=70;
}

void anger(){
  for (int i=0; i<5; i++){
    digitalWrite(Out2, HIGH);
    digitalWrite(OutA5, LOW);
    delay(450);
    digitalWrite(Out2, LOW);
    digitalWrite(OutA5, HIGH);
    delay(450);
  }
  times=45;
}

void watch(){
    digitalWrite(Out2, HIGH);
    digitalWrite(OutA5, LOW);
    delay(150);
    digitalWrite(Out2, LOW);
    digitalWrite(OutA5, LOW);
    delay(3000);
    times=30;
}

