#ifndef DANY_BOT_BUZZER_H_
#define DANY_BOT_BUZZER_H_

namespace DanyBotBuzzer {
	void setUp();
	void playFrequency(uint16_t freq, uint16_t duration, uint8_t volume);
	void playNote(uint8_t note, uint16_t duration, uint8_t volume);
	void play(const int8_t *sequence);
	void playFromProgramSpace(const int8_t *sequence_p);
	void playMode(uint8_t mode);
	uint8_t playCheck();
	uint8_t isPlaying();
	void stopPlaying();
};

#endif