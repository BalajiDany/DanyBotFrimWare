#include "../Constant.h"
#include "DanyBotPushButton.h"

void DanyBotPushButton::setUp() {
	DDRB &= ~(1 << PORTB4);
	PORTB |= (1 << PORTB4);
}

bool DanyBotPushButton::isPressed() {
	return PINB & (1 << PORTB4);
}

bool DanyBotPushButton::isReleased() {
	return !DanyBotPushButton::isPressed();
}

void DanyBotPushButton::waitForPress() {
	do {
		while(DanyBotPushButton::isPressed())
			_delay_ms(DEBOUNCE_DELAY);
	} while(DanyBotPushButton::isPressed());
}

void DanyBotPushButton::waitForRelease() {
	do {
		while(DanyBotPushButton::isReleased())
			_delay_ms(DEBOUNCE_DELAY);
	} while(DanyBotPushButton::isReleased());
}

void DanyBotPushButton::waitForSingleClick() {
	DanyBotPushButton::waitForPress();
	DanyBotPushButton::waitForRelease();
}