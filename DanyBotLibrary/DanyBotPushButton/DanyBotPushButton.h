#ifndef DANY_BOT_PUSH_BUTTON_H_
#define DANY_BOT_PUSH_BUTTON_H_

namespace DanyBotPushButton {
	void setUp();
	bool isPressed();
	bool isReleased();
	void waitForPress();
	void waitForRelease();
	void waitForSingleClick();
}

#endif