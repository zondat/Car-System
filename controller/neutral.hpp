#ifndef __NEUTRAL_H
#define __NEUTRAL_H

#include "gearlevel.hpp"

class Neutral: public GearLevel {
	public:
		Neutral(Car* car);
		void accelerate(int level) override;
		void upGearLevel() override;
		void downGearLevel() override;
};

#endif