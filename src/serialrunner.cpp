/*
 * serialrunner.cpp
 *
 *  Created on: 23/03/2012
 *      Author: michael
 */

#include "serialrunner.h"
#include <avr/io.h>

#define BAUD 9600
#define MYUBRR (F_CPU / 16 / BAUD - 1)

#define RATE  ((uint8_t) 2)
#define FRAME ((uint8_t) 3)
#define CLEAR ((uint8_t) 4)
#define LINE  ((uint8_t) 5)
#define BOX   ((uint8_t) 6)


SerialRunner::SerialRunner(Runner& runner)
: runner(runner)
{
	UBRRH = (MYUBRR >> 8);
	UBRRL = MYUBRR;
	UCSRB = (1 << RXEN) | (1 << TXEN);      // Enable receiver and transmitter
	UCSRC = (1 << URSEL) |(1 << UCSZ1) | (1 << UCSZ0);    // Set frame: 8data, 1 stp
}

uint8_t readByte( void )
{
 	// Wait for incomming data
	while ( !(UCSRA & (1<<RXC)) ) ;
	// Return the data
	return UDR;
}

void SerialRunner::run()
{
    uint8_t command;
    while (true)
    {
        command = readByte();

        switch (command) {
        case CLEAR: {
            runner.get_display().clear();
        } break;
        case FRAME: {
            runner.get_display().update();
        } break;
        case LINE: {
            uint8_t x1 = readByte();
            uint8_t y1 = readByte();
            uint8_t x2 = readByte();
            uint8_t y2 = readByte();
            runner.get_display().line(x1, y1, x2, y2);
        } break;
        case BOX: {
            uint8_t x1 = readByte();
            uint8_t y1 = readByte();
            uint8_t x2 = readByte();
            uint8_t y2 = readByte();
            runner.get_display().box(x1, y1, x2, y2);
        } break;
        }
    }
}

