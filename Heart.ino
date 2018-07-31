const byte ANODE_PINS[8] = {13,12,11,10,9,8,7,6};
const byte CATHODE_PINS[8] = {A3,A2,A1,A0,2,3,4,5};


byte biglove[8][8]=
{
  01,01,01,01,01,01,01,01,  
  01,0,0,01,01,0,0,01,  
  0,0,0,0,0,0,0,0, 
  0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0,    
  01,0,0,0,0,0,0,01,  
  01,01,0,0,0,0,01,01,  
  01,01,01,0,0,01,01,01, 
};

byte sl[8][8]=
{
  01,01,01,01,01,01,01,01,  
  01,01,01,01,01,01,01,01,  
  01,01,0,01,01,0,01,01,  
  01,0,0,0,0,0,0,01,  
  01,0,0,0,0,0,0,01,  
  01,01,0,0,0,0,01,01,  
  01,01,01,0,0,01,01,01,  
  01,01,01,01,01,01,01,01,  
};  

void setup()  
{  
     
  for(int i = 0;i<8;i++)  
  {  
    pinMode(ANODE_PINS[i],OUTPUT);  
    pinMode(CATHODE_PINS[i],OUTPUT);  
  }  
  for(int a=0;a<8;a++)
  {
  digitalWrite(ANODE_PINS[a], HIGH);
    digitalWrite(CATHODE_PINS[a], HIGH);
    }
}  

void loop()  
{  
  for(int i = 0 ; i < 100 ; i++)         
  {  
    display(biglove);                     
  }  
  for(int i = 0 ; i < 50 ; i++)           
  {     
    display(sl);                 
  }  
}  

void display(unsigned char dat[8][8])    
{  
  for(int c = 0; c<8;c++)  
  {  
    digitalWrite(CATHODE_PINS[c],LOW);
  
    //循环  
    for(int r = 0;r<8;r++)  
    {  
      digitalWrite(ANODE_PINS[r],dat[r][c]);  
    }  
    delay(1);  
    Clear();    
  }  
}  
  
void Clear()                          
{  
  for(int i = 0;i<8;i++)  
  {  
    digitalWrite(ANODE_PINS[i],LOW);  
    digitalWrite(CATHODE_PINS[i],HIGH);  
  }  
}

