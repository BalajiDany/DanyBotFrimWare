#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "../Constant.h"
#include "DanyBotSerial.h"

static volatile unsigned char UART_TxBuf[SERIAL_TX_BUFFER_SIZE];
static volatile unsigned char UART_RxBuf[SERIAL_RX_BUFFER_SIZE];
static volatile unsigned char UART_TxHead;
static volatile unsigned char UART_TxTail;
static volatile unsigned char UART_RxHead;
static volatile unsigned char UART_RxTail;
static volatile unsigned char UART_LastRxError;

void DanyBotSerial::setUp() {
	UART_TxHead = 0;
	UART_TxTail = 0;
	UART_RxHead = 0;
	UART_RxTail = 0;
	
	UBRR0H = (uint8_t) (BAUD_RATE >> 8);
	UBRR0L = (uint8_t) BAUD_RATE;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void DanyBotSerial::flush() {
	UART_RxHead = UART_RxTail;
}

uint8_t DanyBotSerial::getAvailableBytes() {
	return (SERIAL_RX_BUFFER_MASK + UART_RxHead - UART_RxTail) % SERIAL_RX_BUFFER_MASK;
}

void DanyBotSerial::writeByte(uint8_t byte) {
	uint8_t tempHead;
	tempHead = (UART_TxHead + 1) & SERIAL_TX_BUFFER_MASK;
	
	while(tempHead == UART_TxTail) {;}
	
	UART_TxBuf[tempHead] = byte;
	UART_TxHead = tempHead;
	UCSR0B |= (1 << UDRIE0);
}

uint8_t DanyBotSerial::readByte() {
	uint8_t tempTail;
	uint8_t serialData;
	
	if(UART_RxHead == UART_RxTail) {
		return SERIAL_NO_DATA;
	}
	
	tempTail = (UART_RxTail + 1) & SERIAL_RX_BUFFER_MASK;
	UART_RxTail = tempTail;
	
	serialData = UART_RxBuf[tempTail];
	return (UART_LastRxError << 8) + serialData;
}

ISR(USART_RX_vect) {
	uint8_t temphead;
	uint8_t serialData;
	uint8_t serialStatus;
	uint8_t lastRxError;
	
	serialStatus = UCSR0A;
	serialData = UDR0;
	
	lastRxError = (serialStatus & ((1 << FE0) | (1 << DOR0)));
	temphead = (UART_RxHead + 1) & SERIAL_RX_BUFFER_MASK;
	
	if(temphead == UART_RxTail) {
		lastRxError = SERIAL_BUFFER_OVERFLOW >> 8;
	} else {
		UART_RxHead = temphead;
		UART_RxBuf[temphead] = serialData;
	}
	UART_LastRxError = lastRxError;
}

ISR(USART_UDRE_vect) {
	uint8_t tempTail;
	
	if(UART_TxHead != UART_TxTail) {
		tempTail = (UART_TxTail + 1) & SERIAL_TX_BUFFER_MASK;
		UART_TxTail = tempTail;
		UDR0 = UART_TxBuf[tempTail];
	} else {
		UCSR0B &= ~(1 << UDRIE0);
	}
}