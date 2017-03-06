#ifndef sht21Library_h
#define sht21Library_h

#include <Arduino.h>

/****************Si7021 & HTU21D Definitions***************************/

#define ADDRESS      0x40

#define TEMP_MEASURE_HOLD  0xE3
#define HUMD_MEASURE_HOLD  0xE5
#define TEMP_MEASURE_NOHOLD  0xF3
#define HUMD_MEASURE_NOHOLD  0xF5
#define TEMP_PREV   0xE0

#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE

#define HTRE        0x02
#define _BV(bit) (1 << (bit))

#define CRC_POLY 0x988000 // Shifted Polynomial for CRC check

// Error codes
#define I2C_TIMEOUT 	998
#define BAD_CRC		999


class sht21Library
{
  public:
    sht21Library(void);

    void iniciar(void);

    float getHumedad(void);
    float getTemperaturaDeHumedad(void);
    float getTemperatura(void);
    uint8_t  checkID(void);

  private:
    uint16_t tomarDatos(uint8_t command);
};


#endif
