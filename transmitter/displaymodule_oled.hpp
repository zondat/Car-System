#ifndef __DISPLAY_MODULE_OLED_H
#define __DISPLAY_MODULE_OLED_H

#include "displaymodule.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class DisplayModule_OLED: public DisplayModule {
	
	public:
		Adafruit_SSD1306 oled;
		DisplayModule_OLED(Adafruit_SSD1306 oled);		
		void init() override;
		void display(int line, String text) override;
		void clear() override;
};

#endif