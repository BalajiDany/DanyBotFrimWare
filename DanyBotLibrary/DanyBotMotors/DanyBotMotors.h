#ifndef DANY_BOT_MOTORS_H_
#define DANY_BOT_MOTORS_H_

namespace DanyBotMotors {
	void setUp();
	void setRightSpeed(uint16_t speed);
	void setLeftSpeed(uint16_t speed);
	void setSpeed(uint16_t lSpeed, uint16_t rSpeed);
}

#endif