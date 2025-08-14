#ifndef __LEVEL_1_H
#define __LEVEL_1_H

#include "gearlevel.hpp"

class Level1: public GearLevel {
	public:
		Level1(Car* car);
		void accelerate(int level) override;
		void upGearLevel() override;
		void downGearLevel() override;
};

#endif