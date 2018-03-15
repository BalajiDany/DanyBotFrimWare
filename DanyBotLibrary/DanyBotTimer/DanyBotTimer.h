#ifndef DANY_BOT_TIMER_H_
#define DANY_BOT_TIMER_H_

namespace DanyBotTimer {
	void setUp();
	void start();
	void stop();
	uint32_t millis();
	uint32_t micros();
}

#endif