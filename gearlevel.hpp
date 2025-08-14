#ifndef __GEAR_LEVEL_H
#define __GEAR_LEVEL_H

#include "config.h"
#include "Arduino.h"

class Car;
class GearLevel {
	public:
		Car *car;
		GearLevel(Car* car);
		virtual void accelerate(int level);
		virtual void upGearLevel();
		virtual void downGearLevel();
};

#endif