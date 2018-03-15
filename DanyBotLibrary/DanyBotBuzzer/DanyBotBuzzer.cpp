#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "../Constant.h"
#include "DanyBotBuzzer.h"


static const uint16_t cs2_divider[] = { 0, 1, 8, 32, 64, 128, 256, 1024 };
uint8_t buzzerInitialized = 0;
volatile uint8_t buzzerFinished = 1;
const int8_t *buzzerSequence = 0;
static volatile uint16_t buzzerTimeout = 0;
static int8_t play_mode_setting = PLAY_AUTOMATIC;
extern volatile uint8_t buzzerFinished;
extern const int8_t *buzzerSequence;
static uint8_t use_program_space;
static uint8_t octave = 4;
static uint16_t whole_note_duration = 2000;
static uint16_t note_type = 4;
static uint16_t duration = 500;
static uint16_t volume = 15;
static uint8_t staccato = 0;
static uint8_t staccato_rest_duration;
static void nextNote();

ISR(TIMER2_OVF_vect) {
	if (buzzerTimeout-- == 0) {
		TIMSK2 = 0;
		sei();
		TCCR2B = (TCCR2B & 0xF8) | 0x3;
		OCR2A = (F_CPU / 64) / 1000;
		OCR2B = 0;
		buzzerFinished = 1;
		if (buzzerSequence && (play_mode_setting == PLAY_AUTOMATIC))
			nextNote();
	}
}

void DanyBotBuzzer::setUp() {
	TIMSK2 = 0;
	TCCR2A = 0x21;
	TCCR2B = 0x0B;
	OCR2A = (F_CPU / 64) / 1000;
	OCR2B = 0;
	DDRD |= (1 << PORTD3);
	sei();
}

void DanyBotBuzzer::playFrequency(uint16_t freq, uint16_t dur, uint8_t volume) {
	buzzerFinished = 0;

	uint16_t timeout;
	uint8_t multiplier = 1;

	if (freq & DIV_BY_10) {
		multiplier = 10;
		freq &= ~DIV_BY_10;
	}

	uint8_t min = 40 * multiplier;
	if (freq < min)
		freq = min;
	if (multiplier == 1 && freq > 10000)
		freq = 10000;

	uint16_t top;
	uint8_t newCS2 = 2;
	uint16_t divider = cs2_divider[newCS2];

	top = (uint16_t)(((F_CPU / 16 * multiplier) + (freq >> 1)) / freq);

	while (top > 255) {
		divider = cs2_divider[++newCS2];
		top = (uint16_t)(((F_CPU / 2 / divider * multiplier) + (freq >> 1)) / freq);
	}

	if (multiplier == 10)
		freq = (freq + 5) / 10;

	if (freq == 1000)
		timeout = dur;
	else
		timeout = (uint16_t)((long)dur * freq / 1000);

	if (volume > 15)
		volume = 15;

	TIMSK2 = 0;

	TCCR2B = (TCCR2B & 0xF8) | newCS2;
	OCR2A = top;
	OCR2B = top >> (16 - volume);
	buzzerTimeout = timeout;

	TIFR2 |= 0xFF;

	TIMSK2 = (1 << TOIE2);
}
void DanyBotBuzzer::playNote(uint8_t note, uint16_t dur, uint8_t volume) {
	uint16_t freq = 0;
	uint8_t offset_note = note - 16;

	if (note == SILENT_NOTE || volume == 0) {
		freq = 1000;
		DanyBotBuzzer::playFrequency(freq, dur, 0);
		return;
	}

	if (note <= 16)
	offset_note = 0;
	else if (offset_note > 95)
	offset_note = 95;

	uint8_t exponent = offset_note / 12;

	switch (offset_note - exponent * 12) {
		case 0:
		freq = 412;
		break;
		
		case 1:
		freq = 437;
		break;
		
		case 2:
		freq = 463;
		break;
		
		case 3:
		freq = 490;
		break;
		
		case 4:
		freq = 519;
		break;
		
		case 5:
		freq = 550;
		break;
		
		case 6:
		freq = 583;
		break;
		
		case 7:
		freq = 617;
		break;
		
		case 8:
		freq = 654;
		break;
		
		case 9:
		freq = 693;
		break;
		
		case 10:
		freq = 734;
		break;
		
		case 11:
		freq = 778;
		break;
	}

	if (exponent < 7) {
		freq = freq << exponent;
		if (exponent > 1)
			freq = (freq + 5) / 10;
		else
			freq += DIV_BY_10;
	}
	else
		freq = (freq * 64 + 2) / 5;

	if (volume > 15)
		volume = 15;
	playFrequency(freq, dur, volume);
}
uint8_t DanyBotBuzzer::isPlaying() {
	return !buzzerFinished || buzzerSequence != 0;
}
void DanyBotBuzzer::play(const int8_t *notes) {
	TIMSK2 = 0;
	buzzerSequence = notes;
	use_program_space = 0;
	staccato_rest_duration = 0;
	nextNote();
}
void DanyBotBuzzer::playFromProgramSpace(const int8_t *notes_p) {
	TIMSK2 = 0;
	buzzerSequence = notes_p;
	use_program_space = 1;
	staccato_rest_duration = 0;
	nextNote();
}
void DanyBotBuzzer::stopPlaying() {
	TIMSK2 = 0;
	
	TCCR2B = (TCCR2B & 0xF8) | 0x3;
	OCR2A = (F_CPU / 64) / 1000;
	OCR2B = 0;

	buzzerFinished = 1;
	buzzerSequence = 0;
}
static int8_t currentCharacter() {
	int8_t c = 0;
	do {
		if (use_program_space)
		c = pgm_read_byte(buzzerSequence);
		else
		c = *buzzerSequence;

		if (c >= 'A' && c <= 'Z')
		c += 'a' - 'A';
	} while (c == ' ' && (buzzerSequence++));

	return c;
}
static uint16_t getNumber() {
	uint16_t arg = 0;
	int8_t c = currentCharacter();
	while (c >= '0' && c <= '9') {
		arg *= 10;
		arg += c - '0';
		buzzerSequence++;
		c = currentCharacter();
	}

	return arg;
}
static void nextNote() {
	uint8_t note = 0;
	uint8_t rest = 0;
	uint8_t tmp_octave = octave;
	uint16_t tmp_duration;
	uint16_t dot_add;

	int8_t c;

	if (staccato && staccato_rest_duration) {
		DanyBotBuzzer::playNote(SILENT_NOTE, staccato_rest_duration, 0);
		staccato_rest_duration = 0;
		return;
	}

	parse_character:

	c = currentCharacter();
	buzzerSequence++;

	switch (c) {
		case '>':
		tmp_octave++;
		goto parse_character;
		
		case '<':
		tmp_octave--;
		goto parse_character;
		
		case 'a':
		note = NOTE_A(0);
		break;
		
		case 'b':
		note = NOTE_B(0);
		break;
		
		case 'c':
		note = NOTE_C(0);
		break;
		
		case 'd':
		note = NOTE_D(0);
		break;
		
		case 'e':
		note = NOTE_E(0);
		break;
		
		case 'f':
		note = NOTE_F(0);
		break;
		
		case 'g':
		note = NOTE_G(0);
		break;
		
		case 'l':
		note_type = getNumber();
		duration = whole_note_duration / note_type;
		goto parse_character;
		
		case 'm':
		if (currentCharacter() == 'l')
			staccato = false;
		else {
			staccato = true;
			staccato_rest_duration = 0;
		}
		buzzerSequence++;
		goto parse_character;
		
		case 'o':
		octave = getNumber();
		tmp_octave = octave;
		goto parse_character;
		
		case 'r':
		rest = 1;
		break;
		
		case 't':
		whole_note_duration = 60 * 400 / getNumber() * 10;
		duration = whole_note_duration / note_type;
		goto parse_character;
		
		case 'v':
		volume = getNumber();
		goto parse_character;
		
		case '!':
		octave = 4;
		whole_note_duration = 2000;
		note_type = 4;
		duration = 500;
		volume = 15;
		staccato = 0;
		tmp_octave = octave;
		tmp_duration = duration;
		goto parse_character;
		
		default:
		buzzerSequence = 0;
		return;
	}

	note += tmp_octave * 12;

	c = currentCharacter();
	while (c == '+' || c == '#') {
		buzzerSequence++;
		note++;
		c = currentCharacter();
	}
	while (c == '-') {
		buzzerSequence++;
		note--;
		c = currentCharacter();
	}


	tmp_duration = duration;
	if (c > '0' && c < '9')
		tmp_duration = whole_note_duration / getNumber();

	dot_add = tmp_duration / 2;
	while (currentCharacter() == '.') {
		buzzerSequence++;
		tmp_duration += dot_add;
		dot_add /= 2;
	}

	if (staccato) {
		staccato_rest_duration = tmp_duration / 2;
		tmp_duration -= staccato_rest_duration;
	}

	DanyBotBuzzer::playNote(rest ? SILENT_NOTE : note, tmp_duration, volume);
}
void DanyBotBuzzer::playMode(uint8_t mode) {
	play_mode_setting = mode;
	if (mode == PLAY_AUTOMATIC)
		DanyBotBuzzer::playCheck();
}
uint8_t DanyBotBuzzer::playCheck() {
	if (buzzerFinished && buzzerSequence != 0)
		nextNote();
	return buzzerSequence != 0;
}
