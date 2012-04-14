/*
 * serialrunner.cpp
 *
 *  Created on: 23/03/2012
 *      Author: michael
 */

#include "serialrunner.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define RATE  ((uint8_t) 2)
#define FRAME ((uint8_t) 3)
#define CLEAR ((uint8_t) 4)
#define LINE  ((uint8_t) 5)
#define BOX   ((uint8_t) 6)

SerialRunner::SerialRunner(Runner& runner)
: runner(runner)
{
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	sei();
}

uint8_t readByte( void )
{
	unsigned int b = UART_NO_DATA;
	while (b == UART_NO_DATA)
		b = uart_getc();
	return b;
}

void SerialRunner::run()
{
    uint8_t command;
    while (true)
    {
        command = readByte();
            runner.get_display().clear();
            runner.get_display().pixelOn(command, 0);
            runner.get_display().update();
/*
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
        */
    }
}

