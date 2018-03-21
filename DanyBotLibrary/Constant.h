#ifndef CONSTANT_H_
#define CONSTANT_H_

#define MILLI_SECOND						1000
#define MICRO_SECOND						MILLI_SECOND * 1000

#define SERG								_SFR_MEM8(0x5f)
#define F_CPU								16000000UL
#define clockCyclesPerMicrosecond()			(F_CPU/1000000)
#define clockCyclesToMicroseconds(a)		((a) / clockCyclesPerMicrosecond())
#define microsecondsToClockCycles(a)		((a) * clockCyclesPerMicrosecond())



//#define BAUD_RATE							115200
#define SERIAL_FRAME_ERROR					0x0800
#define SERIAL_OVERRUN_ERROR				0x0400
#define SERIAL_BUFFER_OVERFLOW				0x0200
#define SERIAL_NO_DATA						0x0100

#define SERIAL_TX_BUFFER_SIZE				32
#define SERIAL_RX_BUFFER_SIZE				32
#define SERIAL_TX_BUFFER_MASK				(SERIAL_TX_BUFFER_SIZE - 1)
#define SERIAL_RX_BUFFER_MASK				(SERIAL_RX_BUFFER_SIZE - 1)

#define BAUD_RATE_2400						416
#define BAUD_RATE_4800						207
#define BAUD_RATE_9600						103
#define BAUD_RATE_14400						68
#define BAUD_RATE_19200						51
#define BAUD_RATE_28800						34
#define BAUD_RATE_38400						25
#define BAUD_RATE_57600						16
#define BAUD_RATE_76800						12
#define BAUD_RATE_115200					8
#define BAUD_RATE_250000					3

#define BAUD_RATE							BAUD_RATE_250000

#define SERIAL_DELAY						(16 * MICRO_SECOND / BAUD_RATE) + 1

#define DEBOUNCE_DELAY						10

#define MAX_MOTOR_SPEED						400

#define MICROSECONDS_PER_TIMER0_OVERFLOW	(clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC							(MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC							((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX							(1000 >> 3)

#define NO_SENSOR							6
#define TIMEOUT								2000
#define	ON_LINE_FILTER						200
#define BASE_FILTER							50
#define MIN_VALUE							0
#define MAX_VALUE							1000
#define LINE_MIN_VALUE						0
#define LINE_MAX_VALUE						MAX_VALUE * (NO_SENSOR - 1)

#define PLAY_AUTOMATIC						0
#define PLAY_CHECK							1
#define NOTE_C(x)							(0 + (x)*12)
#define NOTE_C_SHARP(x)						(1 + (x)*12)
#define NOTE_D_FLAT(x)						(1 + (x)*12)
#define NOTE_D(x)							(2 + (x)*12)
#define NOTE_D_SHARP(x)						(3 + (x)*12)
#define NOTE_E_FLAT(x)						(3 + (x)*12)
#define NOTE_E(x)							(4 + (x)*12)
#define NOTE_F(x)							(5 + (x)*12)
#define NOTE_F_SHARP(x)						(6 + (x)*12)
#define NOTE_G_FLAT(x)						(6 + (x)*12)
#define NOTE_G(x)							(7 + (x)*12)
#define NOTE_G_SHARP(x)						(8 + (x)*12)
#define NOTE_A_FLAT(x)						(8 + (x)*12)
#define NOTE_A(x)							(9 + (x)*12)
#define NOTE_A_SHARP(x)						(10 + (x)*12)
#define NOTE_B_FLAT(x)						(10 + (x)*12)
#define NOTE_B(x)							(11 + (x)*12)
#define SILENT_NOTE							0xFF
#define DIV_BY_10							(1 << 15)

#endif

#include <util/delay.h>
#include <avr/io.h>
