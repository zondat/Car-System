#include "car.hpp"
#include "config.h"
#include "reversegear.hpp"
#include "neutral.hpp"
#include "level1.hpp"
#include "level2.hpp"
#include "level3.hpp"

int currentPwmEsc = PWM_MID, currentPwmYaw = PWM_MID;

Car::Car() {
	reverseGear = new ReverseGear(this);
	neutral = new Neutral(this);
	level1 = new Level1(this);
	level2 = new Level2(this);
	level3 = new Level3(this);
	currentGearLevel = neutral;
}

void Car::init() {	
	calibrate();	
	turn(PWM_MID);
}

void Car::calibrate() {
	setEsc(PWM_MID);
	delay(2500);
}

void Car::accelerate(int level) {
	currentGearLevel->accelerate(level);
}

void Car::turn(int setPwm) {
	setServoYaw(setPwm);
}

void Car::setEsc(int setPwm) {
	//Serial.println("pwm: " + String(setPwm));
	if (setPwm > currentPwmEsc) {
		for (int pwm=currentPwmEsc; pwm<setPwm; pwm+=PWM_STEP) {
			esc.writeMicroseconds(pwm);
			delay(10);
		}		
	}
	else {
		for (int pwm=currentPwmEsc; pwm>setPwm; pwm-=PWM_STEP) {
			esc.writeMicroseconds(pwm);
			delay(10);
		}
	}
	esc.writeMicroseconds(setPwm);
	currentPwmEsc = setPwm;
}

void Car::setServoYaw(int setPwm) {
	if (setPwm > currentPwmYaw) {
		for (int pwm=currentPwmYaw; pwm<setPwm; pwm+=PWM_STEP) {
			yawServo.writeMicroseconds(pwm);
			delay(10);
		}		
	}
	else {
		for (int pwm=currentPwmYaw; pwm>setPwm; pwm-=PWM_STEP) {
			yawServo.writeMicroseconds(pwm);
			delay(10);
		}
	}
	yawServo.writeMicroseconds(setPwm);
	currentPwmYaw = setPwm;
}

void Car::upGearLevel() {
	currentGearLevel->upGearLevel();
}

void Car::downGearLevel() {
	currentGearLevel->downGearLevel();
}

void Car::brake() {
	setEsc(PWM_MID);
}

void Car::setCurrentState(GearLevel * level){
	currentGearLevel = level;
}

void Car::setReverseGear() {
	setCurrentState(reverseGear);
}

void Car::setNeutral() {
	setCurrentState(neutral);
}

void Car::setLevel1() {
	setCurrentState(level1);
}

void Car::setLevel2() {
	setCurrentState(level2);
}

void Car::setLevel3() {
	setCurrentState(level3);
}