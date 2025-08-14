#include "displaymodule_oled.hpp"

DisplayModule_OLED::DisplayModule_OLED(Adafruit_SSD1306 oled) {
	this->oled = oled;
}

void DisplayModule_OLED::init() {
	oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
	oled.clearDisplay();
	oled.setTextSize(1);             // Normal 1:1 pixel scale
	oled.setTextColor(SSD1306_WHITE);        // Draw white text
	oled.setCursor(0,0);   
}

void DisplayModule_OLED::display(int line, String text) {
	oled.setCursor(0, line);  
	oled.print(text.c_str());
}

void DisplayModule_OLED::clear() {
	oled.clearDisplay();  
}
