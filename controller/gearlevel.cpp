#include "gearlevel.hpp"
#include "car.hpp"

GearLevel::GearLevel(Car* car) {
	this->car = car;
}

void GearLevel::accelerate(int level) {}
void GearLevel::upGearLevel() {}
void GearLevel::downGearLevel() {}