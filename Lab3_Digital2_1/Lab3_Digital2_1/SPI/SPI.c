/*
 * SPI.c
 *
 * Created: 11/02/2025 17:03:28
 *  Author: pablo
 */ 

/*
 * SPI.c
 *
 * Created: 11/02/2025 14:22:21
 *  Author: pablo
 */ 
#include "SPI.h"
#include <avr/io.h>

/* Inicializar SPI en modo Maestro o Esclavo */
void spiInit(Spi_Mode mode) {
	if (mode == SPI_MASTER) {
		/* Configurar pines para SPI Maestro */
		DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
		DDRB &= ~(1 << SPI_MISO); // MISO como entrada

		/* Configurar registro SPCR */	
		SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1); // Habilita SPI en modo Maestro, divisor de reloj 16
	}
	else {
		/* Configurar pines para SPI Esclavo */
		DDRB |= (1 << SPI_MISO); // MISO como salida
		DDRB &= ~(1 << SPI_MOSI) & ~(1 << SPI_SCK) & ~(1 << SPI_SS); // MOSI, SCK y SS como entradas
		SPCR = 0;
		/* Configurar registro SPCR */
		SPCR = (1 << SPE); // Habilita SPI en modo Esclavo
		
		// Configurar MSB o LSB primero
		SPCR &= ~(1 << DORD);  // MSB Primero 
		// SPCR |= (1 << DORD);  //
	}
}

/* Enviar un byte a través de SPI */
void spiWrite(uint8_t data) {
	SPDR = data; // Cargar dato en el buffer de transmisión
	while (!(SPSR & (1 << SPIF))); // Esperar a que termine la transmisión
}

/* Leer un byte recibido en SPI */
uint8_t spiRead() {
	while (!(SPSR & (1 << SPIF))); // Esperar a que el dato esté disponible
	return SPDR; // Retornar el dato recibido
}

/* Verificar si hay datos disponibles en SPI */
uint8_t spiDataReady() {
	return (SPSR & (1 << SPIF)); // Retorna 1 si hay datos disponibles
}
