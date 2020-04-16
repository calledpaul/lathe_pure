#ifndef TIMEDACTION_H
#define TIMEDACTION_H

#include <Arduino.h>

#define NO_PREDELAY 0


class Timer {
  
public:
  	Timer(unsigned long intervl){
		previous = 0;
		interval = intervl;
	};
	void reset(){
		previous = millis();
	};
	bool tick(){
	  if ( (millis()-previous >= interval) ) {
		previous = millis();
		return true;
	  }
	  return false;
	};
	void setInterval( unsigned long intervl){
		interval = intervl;
	};
private: 
	unsigned long previous;
	unsigned long interval;
};

class TimedAction {
  
  public:
	TimedAction(unsigned long intervl,void (*function)()){
		active = true;
		previous = 0;
		interval = intervl;
		execute = function;
	};
	TimedAction(unsigned long prev,unsigned long intervl,void (*function)()){
		active = true;
		previous = prev;
		interval = intervl;
		execute = function;
	};
	
	void reset(){
		previous = millis();
	};
	void disable(){
		active = false;
	};
	void enable(){
		active = true;
	};
	void check(){
	  if ( active && (millis()-previous >= interval) ) {
		previous = millis();
		execute();
	  }
	};
	
	void setInterval( unsigned long intervl){
		interval = intervl;
	};

  private: 
	bool active;
	unsigned long previous;
	unsigned long interval;
	void (*execute)();
		
};
#endif

