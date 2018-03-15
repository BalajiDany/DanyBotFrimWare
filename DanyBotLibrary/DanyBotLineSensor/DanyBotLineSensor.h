#ifndef DANY_BOT_LINE_SENSOR_H_
#define DANY_BOT_LINE_SENSOR_H_

namespace DanyBotLineSensor {
	void setUp();
	void reset();
	void emiterOn();
	void emiterOff();
	void calibrate();
	void readCalibrate(uint16_t *sensor);
	void read(uint16_t *sensor);
	void _read(uint16_t *sensor);
	uint16_t readLine(uint16_t *sensor);
}

#endif