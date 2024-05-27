#include <Keyboard.h>

// Constants
const int row_count = 2;
const int col_count = 3;
const int total_keys = row_count * col_count;

// Pinout
byte row_pin[row_count] = {3,4};
byte col_pin[col_count] = {0,1,2};
byte matrix[row_count][col_count];

// Memory
unsigned long press[total_keys];
unsigned long timing[total_keys];

// Configs
bool toggle_key = false;
bool debug = true;

void setup() {
  Serial.begin(115200);
  
  // Pin Initialiasation
  for(int i=0;i<col_count;i++) pinMode(row_pin[i],INPUT_PULLUP);
  for(int i=0;i<row_count;i++) pinMode(col_pin[i],INPUT);

  // Memory Initialisation
  for(int i=0;i<total_keys;i++){
    press[i] = 0;
    timing[i] = millis();
  }

  Keyboard.begin();
}

String readMatrix(){
  String output = "";
  for(int i=0;i<row_count;i++){
    byte cur_row = row_pin[i];
    pinMode(cur_row, OUTPUT);
    digitalWrite(cur_row, LOW);

    for(int j=0;j<col_count;j++){
      byte cur_col = col_pin[j];
      pinMode(cur_col, INPUT_PULLUP);
      matrix[i][j] = digitalRead(cur_col);
      pinMode(cur_col, INPUT);

      output += String(matrix[i][j]);
    }
    pinMode(cur_row, INPUT);
  }
  return output;
}

void press_key(int ind){
  if(toggle_key){
    switch(ind) {
      case 0:
        // Keyboard.press('1');
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('c');
        break;
      case 1:
        // Keyboard.press('2');
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('v');
        break;
      case 2:
        // Keyboard.press('3');
        Keyboard.press(KEY_KP_ENTER);
        break;
      case 3:
        // Keyboard.press('4');
        // Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_UP_ARROW);
        break;
      case 4:
        // Keyboard.press('5');
        // Keyboard.press(KEY_TAB);
        Keyboard.press(KEY_DOWN_ARROW);
        break;
      case 5:
        // Keyboard.press('6');
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_F8);
        break;
    }
  }
}

void release_key(int ind){
  if(toggle_key){
    switch(ind) {
      case 0:
        // Keyboard.release('1');
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.release('c');
        break;
      case 1:
        // Keyboard.release('2');
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.release('v');
        break;
      case 2:
        // Keyboard.release('3');
        Keyboard.release(KEY_KP_ENTER);
        break;
      case 3:
        // Keyboard.release('4');
        // Keyboard.release(KEY_LEFT_ALT);
        Keyboard.release(KEY_UP_ARROW);
        break;
      case 4:
        // Keyboard.release('5');
        // Keyboard.release(KEY_TAB);
        Keyboard.release(KEY_DOWN_ARROW);
        break;
      case 5:
        // Keyboard.release('6');
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.release(KEY_F8);
        break;
    }
  }
}

void loop() {
  String output = readMatrix();
  if(debug) Serial.println(output);
  for(int i=0;i<row_count;i++){
    for(int j=0;j<col_count;j++){
      if(output[i*col_count+j] == '0'){
        if(press[i*col_count+j] == 0){
          press_key(i*col_count+j);
          press[i*col_count+j] = 1;
          timing[i*col_count+j] = millis();
        }
        else if(press[i*col_count+j] == 1){
          if((millis()-timing[i*col_count+j])>=500){
            press_key(i*col_count+j);
            press[i*col_count+j]++;
            timing[i*col_count+j] = millis();
          }
        }
        else{
          if((millis()-timing[i*col_count+j])>=30){
            press_key(i*col_count+j);
            press[i*col_count+j]++;
            timing[i*col_count+j] = millis();
          }
        }
      }
      else{
        press[i*col_count+j] = 0;
        release_key(i*col_count+j);
      }
    }
  }
}
