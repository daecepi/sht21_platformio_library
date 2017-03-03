#include <inttypes.h>
#include <Wire.h>
#include "sht21Library.h"
#include <Arduino.h>

float sht21LibraryClass::getHumidity(void)
{
  uint16_t result;

  //Comenzar comunicación
  Wire.beginTransmission(eSHT2xAddress);	//Comenzar transmision de datos
  Wire.write(eRHumidityHoldCmd);					//Enviar puntero
  delay(100);
  Wire.endTransmission();               	//Finalizar transmision

  Wire.requestFrom(eSHT2xAddress, 3); //Petición de datos al sensor
  //Espera de datos humedad
  while(Wire.available() < 3) {
    ;
  }

  //Guardar resultados
  result = ((Wire.read()) << 8);
  result += Wire.read();
	result &= ~0x0003;   // Limpiar los bits de status

	return (-6.0 + 125.0 / 65536.0 * ((float)(result)));
}

float sht21LibraryClass::getTemperature(void)
{
  uint16_t result;

  //Comenzar comunicación
  Wire.beginTransmission(eSHT2xAddress);	//Comenzar transmision de datos
  Wire.write(eTempHoldCmd);					//send the pointer location
  delay(100);
  Wire.endTransmission();               	//end

  //Espera de datos de humedad
  Wire.requestFrom(eSHT2xAddress, 3); //Petición de datos al sensor
  //Espera de datos de temperatura
  while(Wire.available() < 3) {
    ;
  }

  //Guardar resultados
  result = ((Wire.read()) << 8);
  result += Wire.read();
	result &= ~0x0003;   // Limpiar los bits de status

  return (-46.85 + 175.72 / 65536.0 * ((float)(result)));
}

sht21LibraryClass SHT21;
