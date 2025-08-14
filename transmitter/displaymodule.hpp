#ifndef __DISPLAY_MODULE_H
#define __DISPLAY_MODULE_H

#include <Arduino.h>

class DisplayModule {
	
	public:
		virtual void init() = 0;
		virtual void display(int line, String text) = 0;
		virtual void clear() = 0;
};

#endif