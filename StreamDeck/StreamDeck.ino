#include <Keyboard.h>

// Key (-1 for nothing) Maximum 3 key press per key [Can add more]
//https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
const int keys[6][3] = {
  {KEY_LEFT_CTRL    ,int('c')   ,-1},      // Key 1
  {KEY_LEFT_CTRL    ,int('v')   ,-1},      // Key 2
  {KEY_KP_ENTER     ,-1         ,-1},      // Key 3
  {KEY_UP_ARROW     ,-1         ,-1},      // Key 4
  {KEY_DOWN_ARROW   ,-1         ,-1},      // Key 5
  {KEY_LEFT_CTRL    ,KEY_F8     ,-1}       // Key 6
};

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
bool toggle_key = true;
bool debug = false;

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

// Return string of which key is pressed
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

// Activate key
void press_key(int ind){
  if(toggle_key){
    for(int i=0;i<2;i++){
      if(keys[ind][i] != -1) Keyboard.press(keys[ind][i]);
      else break;
    }
  }
}

// Deactivate key
void release_key(int ind){
  if(toggle_key){
    for(int i=0;i<2;i++){
      if(keys[ind][i] != -1) Keyboard.release(keys[ind][i]);
      else break;
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
