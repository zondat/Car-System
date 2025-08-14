#ifndef __REVERSE_GEAR_H
#define __REVERSE_GEAR_H

#include "gearlevel.hpp"

class ReverseGear: public GearLevel {
	public:
		ReverseGear(Car* car);
		void accelerate(int level) override;
		void upGearLevel() override;
		void downGearLevel() override;
};

#endif