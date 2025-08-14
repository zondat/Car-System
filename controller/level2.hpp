#ifndef __LEVEL_2_H
#define __LEVEL_2_H

#include "gearlevel.hpp"

class Level2: public GearLevel {
	public:
		Level2(Car* car);
		void accelerate(int level) override;
		void upGearLevel() override;
		void downGearLevel() override;
};

#endif