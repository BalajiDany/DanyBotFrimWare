#include "../Constant.h"
#include "DanyBotLed.h"

void DanyBotLed::setUp(){
	DDRB |= (1 << PORTB5);
}

void DanyBotLed::on(){
	PORTB |= (1 << PORTB5);
}

void DanyBotLed::off(){
	PORTB &= ~(1 << PORTB5);
}

void DanyBotLed::toggle(){
	PORTB ^= (1 << PORTB5);
}