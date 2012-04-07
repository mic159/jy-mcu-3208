/*
 * display.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

class Display {
public:
    uint8_t* const buffer;
    Display();
    void update();
    void clear();
    static const uint8_t width = 32;
    static const uint8_t height = 8;
    
	inline void pixelOn(uint8_t x, uint8_t y)
    {
    	if (x > width) return;
    	if (y > height) return;
		buffer[x] |= 1 << y;
	}
	
	void line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	void box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
};

#endif /* DISPLAY_H_ */
