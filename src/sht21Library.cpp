#if defined(ARDUINO)
#include "Wire.h"
#include "sht21Library.h"
#endif

//Inicialización
sht21Library::sht21Library(){}

void sht21Library::iniciar()
{
  Wire.begin();

  uint8_t ID_Temp_Hum = checkID();

  int x = 0;

  if(ID_Temp_Hum == 0x15)//Ping CheckID register
    x = 1;
  else if(ID_Temp_Hum == 0x32)
    x = 2;
  else
    x = 0;

  if(x == 1)
  {
    Serial.println("Si7021 encontrado");
    //Serial.println(ID_Temp_Hum, HEX);
  }
  else if(x == 2)
  {
    Serial.println("HTU21D encontrado");
    //Serial.println(ID_Temp_Hum, HEX);
  }
  else
  	Serial.println("Ningun dispositivo detectado");
  	//Serial.println(ID_Temp_Hum, HEX);
}

float sht21Library::getHumedad()
{
	// Measure the relative humidity
	uint16_t RH_Code = tomarDatos(HUMD_MEASURE_NOHOLD);
	float resultado = (125.0*RH_Code/65536)-6;
	return resultado;
}

float sht21Library::getTemperaturaDeHumedad()
{
	// Medir temperatura de la anterior medición de humedad.
	uint16_t temp_Code = tomarDatos(TEMP_PREV);
	float resultado = (175.25*temp_Code/65536)-46.85;
	return resultado;
}

float sht21Library::getTemperatura()
{
	// Medir temperatura
	uint16_t temp_Code = tomarDatos(TEMP_MEASURE_NOHOLD);
	float resultado = (175.25*temp_Code/65536)-46.85;
	return resultado;
}

uint8_t sht21Library::checkID()
{
	uint8_t ID_1;

 	// Check device ID
	Wire.beginTransmission(ADDRESS);
	Wire.write(0xFC);
	Wire.write(0xC9);
	Wire.endTransmission();

    Wire.requestFrom(ADDRESS,1);

    ID_1 = Wire.read();

    return(ID_1);
}

uint16_t sht21Library::tomarDatos(uint8_t command)
{

	uint16_t nBytes = 3;
	// if we are only reading old temperature, read olny msb and lsb
	if (command == 0xE0) nBytes = 2;

	Wire.beginTransmission(ADDRESS);
	Wire.write(command);
	Wire.endTransmission();
	// When not using clock stretching (*_NOHOLD commands) delay here
	// is needed to wait for the measurement.
	// According to datasheet the max. conversion time is ~22ms
	 delay(100);

	Wire.requestFrom(ADDRESS,nBytes);
	//Wait for data
	int counter = 0;
	while (Wire.available() < nBytes){
	  delay(1);
	  counter ++;
	  if (counter >100){
	    // Timeout: Sensor did not return any data
	    return 100;
	  }
	}

	unsigned int msb = Wire.read();
	unsigned int lsb = Wire.read();
	// Clear the last to bits of LSB to 00.
	// According to datasheet LSB of RH is always xxxxxx10
	lsb &= 0xFC;
	unsigned int datos = msb << 8 | lsb;

	return datos;
}
