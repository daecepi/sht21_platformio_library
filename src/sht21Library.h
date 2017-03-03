#ifndef sht21Library_h
#define sht21Library_h

#include <inttypes.h>

typedef enum {
    eSHT2xAddress = 0x40,
} HUM_SENSOR_T;

typedef enum {
    eTempHoldCmd		= 0xE3,
    eRHumidityHoldCmd	= 0xE5,
    eTempNoHoldCmd      = 0xF3,
    eRHumidityNoHoldCmd = 0xF5,
} HUM_MEASUREMENT_CMD_T;

class sht21LibraryClass
{
  public:
    float getHumidity(void);
    float getTemperature(void);
};

extern sht21LibraryClass SHT21;

#endif
