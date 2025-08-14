#include "level1.hpp"
#include "car.hpp"

Level1::Level1(Car* car) : GearLevel(car) {}

void Level1::accelerate(int pwm) {
	int newPwm = map(pwm, PWM_MID, PWM_MAX, PWM_MID, 1700);
	car->setEsc(newPwm);
}

void Level1::upGearLevel() {
	car->setNeutral();
}

void Level1::downGearLevel() {
	car->setLevel2();
}