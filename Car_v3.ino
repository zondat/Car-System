/******************************/
/******* Car setting **********/
#include "car.hpp"

Car car;
Servo servo1, servo2;

/********************************/
/******* Radio setting **********/
#include "SPI.h"
#include "NRFLite.h"
#include "mess.h"

NRFLite _radio;
RadioPacket _radioData, _lastData;
uint8_t nbMisses = 0;

void init_radio() {
  while (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
    Serial.println("Cannot communicate with radio");
    delay(1000);
  }
  Serial.println("Connected to radio");
}

void handle_cmd(RadioPacket _mess) {
  if (_mess.upGear) car.upGearLevel();
  if (_mess.downGear) car.downGearLevel();
  
  if (_mess.brake) car.brake();
  else {
    int pwm;

    // Accelerate
    if (_mess.x<ADC_MID) _mess.x = ADC_MID;
    pwm = map(_mess.x, ADC_MIN, ADC_MAX, PWM_MIN, PWM_MAX);
    car.accelerate(pwm);

    // Turn
    pwm = map(_mess.y, ADC_MIN, ADC_MAX, PWM_MIN, PWM_MAX);
    car.turn(pwm);
  }
}

/********************************/
/********************************/
void setup() {
  Serial.begin(115200);

  // Init car
  servo1.attach(PIN_ESC);
	servo2.attach(PIN_SERVO_YAW);
  car.esc = servo1;
  car.yawServo = servo2;
  car.init();
  car.turn(1500);

  // Init RF module
  init_radio();
}

void loop() {
  while (true) {
    if (_radio.hasData()) {
      // Serial.println("Received cmd");
      _lastData = _radioData;
      _radio.readData(&_radioData);
      handle_cmd(_radioData);
      nbMisses = 0;
    } else {
      nbMisses ++;
      if (nbMisses<NB_MAX_MISSED) handle_cmd(_lastData);
      else {
        car.brake();
        nbMisses = NB_MAX_MISSED;
      }
      break;
    } 
  }
  delay(45);
}
