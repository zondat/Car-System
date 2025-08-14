#ifndef __LEVEL_3_H
#define __LEVEL_3_H

#include "gearlevel.hpp"

class Level3: public GearLevel {
	public:
		Level3(Car* car);
		void accelerate(int level) override;
		void upGearLevel() override;
		void downGearLevel() override;
};

#endif