#ifndef CONSTANT_H_
#define CONSTANT_H_

#define SERG								_SFR_MEM8(0x5f)
#define F_CPU								16000000UL
#define clockCyclesPerMicrosecond()			(F_CPU/1000000)
#define clockCyclesToMicroseconds(a)		( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a)		( (a) * clockCyclesPerMicrosecond() )

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
#define NOTE_C(x)							( 0 + (x)*12)
#define NOTE_C_SHARP(x)						( 1 + (x)*12)
#define NOTE_D_FLAT(x)						( 1 + (x)*12)
#define NOTE_D(x)							( 2 + (x)*12)
#define NOTE_D_SHARP(x)						( 3 + (x)*12)
#define NOTE_E_FLAT(x)						( 3 + (x)*12)
#define NOTE_E(x)							( 4 + (x)*12)
#define NOTE_F(x)							( 5 + (x)*12)
#define NOTE_F_SHARP(x)						( 6 + (x)*12)
#define NOTE_G_FLAT(x)						( 6 + (x)*12)
#define NOTE_G(x)							( 7 + (x)*12)
#define NOTE_G_SHARP(x)						( 8 + (x)*12)
#define NOTE_A_FLAT(x)						( 8 + (x)*12)
#define NOTE_A(x)							( 9 + (x)*12)
#define NOTE_A_SHARP(x)						(10 + (x)*12)
#define NOTE_B_FLAT(x)						(10 + (x)*12)
#define NOTE_B(x)							(11 + (x)*12)
#define SILENT_NOTE							0xFF
#define DIV_BY_10							(1 << 15)

#endif

#include <util/delay.h>
#include <avr/io.h>
