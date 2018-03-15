#include <Constant.h>
#include <DanyBotLed/DanyBotLed.h>
#include <DanyBotPushButton/DanyBotPushButton.h>
#include <DanyBotMotors/DanyBotMotors.h>
#include <DanyBotTimer/DanyBotTimer.h>
#include <DanyBotLineSensor/DanyBotLineSensor.h>
#include <DanyBotBuzzer/DanyBotBuzzer.h>

void setUp();

int main(void)
{
	uint16_t sensor[NO_SENSOR];
	setUp();
    while (1) {
	    DanyBotLed::toggle();
		DanyBotPushButton::waitForSingleClick();
		DanyBotMotors::setSpeed(20, 20);
		DanyBotTimer::start();
		DanyBotTimer::millis();
		DanyBotTimer::micros();
		DanyBotTimer::stop();
		DanyBotLineSensor::calibrate();
		DanyBotLineSensor::readLine(sensor);
		DanyBotBuzzer::playNote(NOTE_E(5),112, 15);
    }
}

void setUp(){
	DanyBotTimer::setUp();
	DanyBotLed::setUp();
	DanyBotPushButton::setUp();
	DanyBotMotors::setUp();
	DanyBotLineSensor::setUp();
	DanyBotBuzzer::setUp();
}