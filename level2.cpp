#include "level2.hpp"
#include "car.hpp"

Level2::Level2(Car* car) : GearLevel(car) {}

void Level2::accelerate(int pwm) {
	int newPwm = map(pwm, PWM_MID, PWM_MAX, PWM_MID, 2000);
	car->setEsc(newPwm);
}

void Level2::upGearLevel() {
	car->setLevel1();
}

void Level2::downGearLevel() {
	car->setLevel3();
}