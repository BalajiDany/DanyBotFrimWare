#ifndef DANY_BOT_SERIAL_H__
#define DANY_BOT_SERIAL_H__

namespace DanyBotSerial {
	void setUp();
	void writeByte(uint8_t byte);
	uint8_t readByte();
	uint8_t getAvailableBytes();
	void flush();
}

#endif
