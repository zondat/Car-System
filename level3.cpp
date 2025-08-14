#include "level3.hpp"
#include "car.hpp"

Level3::Level3(Car* car) : GearLevel(car) {}

void Level3::accelerate(int pwm) {
	car->setEsc(pwm);
}

void Level3::upGearLevel() {
	car->setLevel2();
}

void Level3::downGearLevel() {}