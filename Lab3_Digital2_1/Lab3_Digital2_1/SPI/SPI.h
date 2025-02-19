/*
 * SPI.h
 *
 * Created: 11/02/2025 17:03:21
 *  Author: pablo
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdint.h>

/* Pines SPI en el ATmega328P */
#define SPI_MOSI  PB3  // Maestro: Salida | Esclavo: Entrada
#define SPI_MISO  PB4  // Maestro: Entrada | Esclavo: Salida
#define SPI_SCK   PB5  // Reloj de comunicación
#define SPI_SS    PB2  // Selección de esclavo

/* Definiciones de Modos */
typedef enum {
	SPI_MASTER = 0b01010000,   // Maestro, divisor de reloj 16
	SPI_SLAVE  = 0b01000000    // Esclavo
} Spi_Mode;

/* Funciones */
void spiInit(Spi_Mode mode);
void spiWrite(uint8_t data);
uint8_t spiRead();
uint8_t spiDataReady();



#endif /* SPI_H_ */