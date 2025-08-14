#ifndef __CAR_H
#define __CAR_H

#include "gearlevel.hpp"
#include <Servo.h>

class Car {
	
	public:
		Car();
		Servo esc, yawServo;
		GearLevel *currentGearLevel, *reverseGear, *neutral, *level1, *level2, *level3;
		
		void init();
		void calibrate();
		void setEsc(int pwm);
		void setServoYaw(int pwm);
		void accelerate(int level);
		void turn(int yaw);
		void brake();
		void upGearLevel();
		void downGearLevel();
		void setCurrentState(GearLevel * level);
		void setReverseGear();
		void setNeutral();
		void setLevel1();
		void setLevel2();
		void setLevel3();
};

#endif