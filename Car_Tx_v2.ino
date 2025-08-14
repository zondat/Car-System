/*

Demonstrates simple RX and TX operation.
Any of the Basic_RX examples can be used as a receiver.
Please read through 'NRFLite.h' for a description of all the methods available in the library.

Radio    Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND
*/

const static uint8_t RADIO_ID = 1;              // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0;  // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
const static uint8_t PIN_RADIO_IRQ = 8;

/********************************/
/******* Message structure ******/
#include "SPI.h"
#include "NRFLite.h"
#include "mess.h"

NRFLite _radio;
RadioPacket _radioData;

void init_radio() {
  while (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
    Serial.println("Cannot communicate with radio");
    delay(1000);
  }
  Serial.println("Connected to radio");
}

/********************************/
/********** Joystick ************/
#define PIN_JOYSTICK_SW A2
#define PIN_JOYSTICK_RX A0
#define PIN_JOYSTICK_RY A1
#define ADC_MAX 1023
#define ADC_MIN 0

#define THRESHOLD 35
bool inverted = false;


void init_joystick() {
  pinMode(PIN_JOYSTICK_SW, INPUT);
  pinMode(PIN_JOYSTICK_RX, INPUT);
  pinMode(PIN_JOYSTICK_RY, INPUT);
}

/*********************************/
/********** Gearstick ************/
#define PIN_GEAR_UP     2
#define PIN_GEAR_DOWN   3

bool gearUp = false;
bool gearDown = false;

void init_gearstick() {
  pinMode(PIN_GEAR_DOWN, INPUT_PULLUP);
  pinMode(PIN_GEAR_UP, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_GEAR_UP), handle_gear_up, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_GEAR_DOWN), handle_gear_down, FALLING);
}

void handle_gear_up() {
  gearUp = true;
}

void handle_gear_down() {
  gearDown = true;
}

/**************************************/
/********** Display Module ************/
// #include "displaymodule_oled.hpp"
// #include <SPI.h>
// #include <Wire.h>

// Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// DisplayModule_OLED displayModule(oled);

/********************************/
void setup() {
  Serial.begin(115200);
  // displayModule.init();
  init_joystick();
  init_gearstick();
  init_radio();
}

void loop() {
  if (digitalRead(PIN_JOYSTICK_SW)) inverted = !inverted;
  _radioData.x = analogRead(PIN_JOYSTICK_RX);
  _radioData.y = analogRead(PIN_JOYSTICK_RY);
  _radioData.downGear = gearDown;
  _radioData.upGear = gearUp;

  if (_radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData))) {
    // displayModule.clear();
    // displayModule.display(0, "x: " + String(_radioData.x));
    // displayModule.display(1, "y: " + String(_radioData.y));
    // if (gearUp) displayModule.display(2, "Gear: Up");
    // else if (gearDown) displayModule.display(2, "Gear: Down");
    // else displayModule.display(2, "Gear: None");
  }
  // _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::NO_ACK);
  // _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData));

  gearDown = false;
  gearUp = false;
  delay(1500);
}
