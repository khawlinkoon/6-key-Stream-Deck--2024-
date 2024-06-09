# 6-key Stream Deck (2024)
 A stream deck with 6 keys using Seeeduino Xiao.

## Prerequisite
Download the board to Arduino IDE using this link: https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

## How to change key
#### Change the value for variable keys in .ino file. 
#### Possible keys shown here: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
#### Ensure that all alphabets are casted to integer. -1 for no keys. Simultaneous key press possible

#### Example:
```
const int keys[6][3] = {
 {KEY_LEFT_CTRL    ,int('c')   ,-1},      // Key 1: Copy shortcut
 {KEY_LEFT_CTRL    ,int('v')   ,-1},      // Key 2: Paste shortcut
 {KEY_KP_ENTER     ,-1         ,-1},      // Key 3: Enter
 {KEY_UP_ARROW     ,-1         ,-1},      // Key 4: Up
 {KEY_DOWN_ARROW   ,-1         ,-1},      // Key 5: Down
 {KEY_LEFT_CTRL    ,-1         ,-1}       // Key 6: Ctrl
};
```

## Final product
<div align="center">
  <img width="100%" src="https://github.com/khawlinkoon/6-key-Stream-Deck--2024-/blob/main/Product.png">
</div>

## Created by
#### Khaw Lin Koon (khawlinkoon@gmail.com)