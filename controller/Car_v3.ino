/******************************/
/******* Car setting **********/
#include "car.hpp"


Car car;
Servo servo1, servo2, servo3;

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
    
  // Accelerate
  handle_accel(_mess.x);
  // Turn
  handle_turn(_mess.y);
  // Headtrack
  handle_head_track(_mess.yaw);
}

void handle_accel(uint16_t accel) {
  car.accelerate(accel);
}

void handle_turn(uint16_t yaw) {
  int pwm = map(yaw, ADC_MIN, ADC_MAX, PWM_MIN, PWM_MAX);
  car.turn(pwm);
}

/********************************/
/******* Headtracking  **********/
void init_headtrack() {
  servo3.attach(PIN_SERVO_CAM);
  servo3.write(90);
}

void handle_head_track(uint8_t yaw) {
  servo3.write(yaw);
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

  // Init RF module
  init_radio();

  init_headtrack();
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
      car.brake();
      handle_turn(_lastData.y);
      handle_head_track(_lastData.yaw);
      // nbMisses ++;
      // if (nbMisses<NB_MAX_MISSED) handle_cmd(_lastData);
      // else {
      //   car.brake();
      //   nbMisses = NB_MAX_MISSED;
      // }
      // break;
    } 
  }
  delay(100);
}
