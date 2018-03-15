#include "../Constant.h"
#include "../DanyBotTimer/DanyBotTimer.h"
#include "DanyBotLineSensor.h"

uint16_t *calibratedMax;
uint16_t *calibratedMin;
bool onLine = false;

void DanyBotLineSensor::setUp() {
	DanyBotLineSensor::reset();
	DDRD |= (1 << PORTD2);
}

void DanyBotLineSensor::reset() {
	for(uint8_t i = 0; i < NO_SENSOR; i++) {
		calibratedMax[i] = 0;
		calibratedMin[i] = TIMEOUT;
	}
	DanyBotLineSensor::emiterOff();
}

void DanyBotLineSensor::emiterOn() {
	PORTD |= (1 << PORTD2);
	_delay_us(100);
}

void DanyBotLineSensor::emiterOff() {
	PORTD &= ~(1 << PORTD2);
	_delay_us(100);
}

void DanyBotLineSensor::calibrate() {
	uint16_t sensor[NO_SENSOR];
	for(uint8_t i = 0; i < 10; i++) {
		read(sensor);
		for(uint8_t j = 0; j < NO_SENSOR; j++) {
			if(i == 0 || sensor[j] > calibratedMin[j])
				calibratedMin[j] = sensor[j];
			if(i == 0 || sensor[j] < calibratedMax[j])
				calibratedMax[j] = sensor[j];
		}
	}
}

void DanyBotLineSensor::readCalibrate(uint16_t *sensor) {
	uint16_t denominator;
	read(sensor);
	for (uint8_t i = 0; i < NO_SENSOR; i++) {
		denominator = calibratedMax[i] - calibratedMin[i];
		int16_t temp = 0;
		if(denominator != 0)
			temp = (((int32_t)sensor[i] - calibratedMin[i]) * MAX_VALUE / denominator);
			sensor[i]  = temp;
		if(temp < MIN_VALUE)
			sensor[i] = MIN_VALUE;
		if(temp > MAX_VALUE)
			sensor[i] = MAX_VALUE;
	}
}

uint16_t DanyBotLineSensor::readLine(uint16_t *sensor) {
	onLine = false;
	static uint16_t previousValue;
	readCalibrate(sensor);
	uint32_t avg = 0;
	uint16_t sum = 0;
	for(uint8_t i = 0; i < NO_SENSOR; i++) {
		if(sensor[i] > BASE_FILTER) {
			avg += (uint32_t)sensor[i] * (i * MAX_VALUE);
			sum += sensor[i];
			if(sensor[i] > ON_LINE_FILTER)
				onLine = true;
		}
	}
	if(!onLine) {
		return previousValue < (LINE_MAX_VALUE / 2) ? LINE_MIN_VALUE : LINE_MAX_VALUE;
	}
	previousValue = avg / sum;
	return previousValue;
}

void DanyBotLineSensor::read(uint16_t *sensor) {
	DanyBotLineSensor::emiterOn();
	DanyBotLineSensor::_read(sensor);
	DanyBotLineSensor::emiterOff();
}

void DanyBotLineSensor::_read(uint16_t *sensor) {
	
	for (uint8_t i = 0; i < NO_SENSOR; i++) {
		sensor[i] = TIMEOUT;
	}
	
	DDRB |= (1 << PORTB3);
	DDRD |= (1 << PORTD4) | (1 << PORTD5);
	DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2);
	
	PORTB |= (1 << PORTB3);
	PORTD |= (1 << PORTD4) | (1 << PORTD5);
	PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2);
	
	_delay_us(10);
	
	DDRB &= ~(1 << PORTB3);
	DDRD &= ~(1 << PORTD4) & ~(1 << PORTD5);
	DDRC &= ~(1 << PORTC0) & ~(1 << PORTC1) & ~(1 << PORTC2);
	
	PORTB &= ~(1 << PORTB3);
	PORTD &= ~(1 << PORTD4) & ~(1 << PORTD5);
	PORTC &= ~(1 << PORTC0) & ~(1 << PORTC1) & ~(1 << PORTC2);
	
	DanyBotTimer::start();
	uint32_t timeStamp = DanyBotTimer::micros();
	while (timeStamp < TIMEOUT) {
		if(!(PORTD & ~(1 << PORTD4)))
			sensor[0] = timeStamp;
				
		if(!(PORTC & ~(1 << PORTC2)))
			sensor[1] = timeStamp;
				
		if(!(PORTB & ~(1 << PORTB3)))
			sensor[2] = timeStamp;
				
		if(!(PORTC & ~(1 << PORTC0)))
			sensor[3] = timeStamp;
				
		if(!(PORTC & ~(1 << PORTC1)))
			sensor[4] = timeStamp;
				
		if(!(PORTC & ~(1 << PORTC2)))
			sensor[5] = timeStamp;
		
		timeStamp = DanyBotTimer::micros();
	}
	DanyBotTimer::stop();
}