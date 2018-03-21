#include <Constant.h>
#include <DanyBotLed/DanyBotLed.h>
#include <DanyBotPushButton/DanyBotPushButton.h>
#include <DanyBotMotors/DanyBotMotors.h>
#include <DanyBotTimer/DanyBotTimer.h>
#include <DanyBotLineSensor/DanyBotLineSensor.h>
#include <DanyBotBuzzer/DanyBotBuzzer.h>
#include <DanyBotSerial/DanyBotSerial.h>

void setUp();

int main(void) {
	uint16_t sensor[NO_SENSOR];
	setUp();
	uint8_t count = 32;
	uint8_t bCount = 0;
	uint8_t value[256];
	uint8_t ReceivedByte;
	//DanyBotSerial::writeByte(1);
	//DanyBotSerial::readByte();
	//DanyBotSerial::isAvailableToRead();
	//DanyBotSerial::isAvailableToWrite();
    while (1) {
	    DanyBotLed::toggle();
		//DanyBotPushButton::waitForSingleClick();
		//DanyBotMotors::setSpeed(20, 20);
		//DanyBotTimer::start();
		//DanyBotTimer::millis();
		//DanyBotTimer::micros();
		//DanyBotTimer::stop();
		//DanyBotLineSensor::calibrate();
		//DanyBotLineSensor::readLine(sensor);
		//DanyBotBuzzer::playNote(NOTE_E(5),112, 15);
		//count = 0;
		//while (DanyBotSerial::getAvailableBytes() != 0) {
		//	int sByte = DanyBotSerial::readByte();
		//	DanyBotSerial::writeByte(sByte);
		//}
		
		//if(bCount != 0){
		//	DanyBotSerial::writeByte(10);
		//	DanyBotSerial::writeByte(bCount+48);
			
		//	for(uint8_t pr = 0; pr < bCount; pr++) {
		//		DanyBotSerial::writeByte(value[pr]);
		//		value[pr] = 0;
		//	}
		//}
		//bCount = 0;
		if(count == 126) {
			DanyBotSerial::writeByte(10);
			count = 32;
		}
		DanyBotSerial::writeByte(count++);
		_delay_ms(60);
    }
}

void setUp() {
	DanyBotTimer::setUp();
	DanyBotLed::setUp();
	DanyBotPushButton::setUp();
	DanyBotMotors::setUp();
	DanyBotLineSensor::setUp();
	DanyBotBuzzer::setUp();
	DanyBotSerial::setUp();
}