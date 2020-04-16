#ifndef DEF_DISPLAY_H
#define DEF_DISPLAY_H

#include "Utils.h"
#include <LiquidCrystal_I2C.h>

class Display {
private:
  LiquidCrystal_I2C _lcd;

  String _buff[32];
  int _speedVal;
  bool suspended = false;
  String _modes[5] = {" X - TURN ", " Y - FACE ", "EXT THREAD", "INT THREAD", " FUNCTION "};
    

  void write(int x, int y, String* info) {
    int pos = y * 16 + x;
    if (_buff[pos] != *info) {
      _buff[pos] = *info;
      _lcd.setCursor(x, y);
      _lcd.print(*info);
    }
  }
public:
  Display() : _lcd(0x27, 16, 2) {};

  void init() {
    _lcd.init();
    _lcd.backlight();
  }

  void mode(int m) {
    write(0, 0, &_modes[m]);
  }

  void _speed() {
    float s = float(_speedVal) / 100;
    char buff[5];
    dtostrf(s, 1, 2, buff);    
    write(1, 1, new String(buff));
  }

  void speed(int s) {
    _speedVal = s;
    if (!suspended) {
      _speed();
    }
  }

  void suspend() {
    suspended = true;
  }

  void refresh() {
    suspended = false;
    _speed();
  }
  

};

#endif