#include <stdbool.h>

const byte ANODE_PINS[8] = {13,12,11,10,9,8,7,6};
const byte CATHODE_PINS[8] = {A3,A2,A1,A0,2,3,4,5};
const int button=A5;

enum States { GAME, GAME_OVER };

typedef struct {
  States state = GAME;
  bool is_jump = false;
  int jump_remain = 0; // How many time of jump left
  byte stone_pos = 7;
} GameState;
int delta = 0; // Delta time

GameState state;

byte canvas[8][8] = {{0}};

const byte gameover[8][8] = {
  0,1,1,1,1,1,1,0,  
  1,1,0,1,1,0,1,1,  
  1,1,0,1,1,0,1,1, 
  0,1,1,1,1,1,1,0,  
  0,1,1,1,1,1,1,0,    
  0,0,1,1,1,1,0,0,  
  0,0,1,0,0,1,0,0,  
  0,0,1,1,1,1,0,0,
};

void update_stone() {
  if (state.stone_pos != 0) {
    --state.stone_pos;
  } else {
    state.stone_pos = 7;
  }
}

bool is_collide() {
  return state.stone_pos == 0 && !state.is_jump;
}

// Main update function of the game
void update() {
  if (state.is_jump) {
      --state.jump_remain;

      if (state.jump_remain <= 0) {
        state.is_jump = false;
      }
  }
    
  update_stone();

  if (is_collide()) {
    state.state = GAME_OVER;
  }
}

void render_canvas() {
  for (byte i = 0; i < 8; ++i) {
    for (byte j = 0; j < 8; ++j) {
      canvas[i][j] = 0;
    }
  }
  
  if (!state.is_jump)
  {
    canvas[7][0] = 1;
  }
  else
  {
    canvas[4][0] = 1;
  }

  canvas[6][state.stone_pos] = 1;
  canvas[7][state.stone_pos] = 1;
  display(canvas);
}

void loop()
{

  
  change();

  if (state.state == GAME) {
  if (delta >= 10) {
    update();
    delta = 0;
  } else {
    ++delta;
  }
    
    render_canvas();
  } else {
    display(gameover);
  }

}

void setup(){
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
    pinMode(button,INPUT_PULLUP);
  }
  for(byte c=0;c<8;c++){
    digitalWrite(ANODE_PINS[c], HIGH);
    digitalWrite(CATHODE_PINS[c], HIGH);
  }
  Serial.begin(9600);
  
  }
void change(){
  int voltage=digitalRead(button);
  Serial.println(voltage);
  if (state.state == GAME) {
    if (voltage==0 && !state.is_jump) {
      state.is_jump = true;
      state.jump_remain = 3;
    }
  } else if (state.state == GAME_OVER) {
    if (voltage == 0) {
      state.state = GAME;
      state.is_jump = false;
      state.jump_remain = 0; // How many time of jump left
      state.stone_pos = 7;
    }
  }

     
  }

void display(byte pattern[8][8]) {
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 8; j++) {
      // look up in pattern whether this LED should be on or off
      if (pattern[i][j]) {
        // if LED should be on, activate cathode (-) wire
        digitalWrite(CATHODE_PINS[j], LOW);
      } else {
        // else deactivate it
        digitalWrite(CATHODE_PINS[j], HIGH);
      }
    }
    // activate anode (+) wire
    digitalWrite(ANODE_PINS[i], LOW);
    // wait a short time
    delayMicroseconds(1000);
    // deactivate anode (+) wire
    digitalWrite(ANODE_PINS[i], HIGH);
    delayMicroseconds(1000);
  }
}

