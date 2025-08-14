#include "neutral.hpp"
#include "car.hpp"

Neutral::Neutral(Car* car) : GearLevel(car) {}

void Neutral::accelerate(int level) {
	car->setEsc(PWM_MID);
}

void Neutral::upGearLevel() {
	car->setReverseGear();
}

void Neutral::downGearLevel() {
	car->setLevel1();
}