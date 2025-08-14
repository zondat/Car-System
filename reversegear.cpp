#include "reversegear.hpp"
#include "car.hpp"

ReverseGear::ReverseGear(Car* car) : GearLevel(car) {}

void ReverseGear::accelerate(int pwm) {
	int delta = pwm - PWM_MID;
	delta = delta * 2 / 3; // Deccelerate
	int newPwm = PWM_MID - delta; 
	car->setEsc(newPwm);
}

void ReverseGear::upGearLevel() {
	car->setReverseGear();
}

void ReverseGear::downGearLevel() {
	car->setLevel1();
}