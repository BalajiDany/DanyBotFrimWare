#include "../Constant.h"
#include "DanyBotMotors.h"

void DanyBotMotors::setUp() {
	DDRD |= (1 << PORTD7);
	DDRB |= (1 << PORTB0);
	
	TCCR1A = (1 << COM0A1) | (1 << COM0B1);
	TCCR1B = (1 << WGM13) | (1 << CS10);
	ICR1 = MAX_MOTOR_SPEED;
}

void DanyBotMotors::setRightSpeed(uint16_t speed) {
	bool reverse = speed < 0;
	if(reverse) {
		speed = -speed;
		PORTD &= ~(1 << PORTD7);
	} else {
		PORTD |= (1 << PORTD7);
	}
	if(speed > MAX_MOTOR_SPEED) {
		OCR1A = MAX_MOTOR_SPEED;
	} else {
		OCR1A = speed;	
	}
}

void DanyBotMotors::setLeftSpeed(uint16_t speed) {
	bool reverse = speed < 0;
	if(reverse) {
		speed = -speed;
		PORTB &= ~(1 << PORTB0);
	} else {
		PORTB |= (1 << PORTB0);
	}
	if(speed > MAX_MOTOR_SPEED){
		OCR1B = MAX_MOTOR_SPEED;
	} else {
		OCR1B = speed;
	}
}

void DanyBotMotors::setSpeed(uint16_t lSpeed, uint16_t rSpeed) {
	DanyBotMotors::setLeftSpeed(lSpeed);
	DanyBotMotors::setRightSpeed(rSpeed);
}