/*
 * display.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

class Display
{
public:
	uint8_t* const buffer;
	Display(uint8_t offset_x = 0, uint8_t offset_y = 0);
	void update();
	void clear();
	static const uint8_t width = 32;
	static const uint8_t height = 8;
	
	inline void pixelOn(int8_t x, int8_t y)
	{
		x += offset_x;
		y += offset_y;
		if (x >= width || x < 0) return;
		if (y >= height|| y < 0) return;
		buffer[x] |= 1 << y;
	}
		
	void line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	void box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
private:
	uint8_t offset_x;
	uint8_t offset_y;
};

#endif /* DISPLAY_H_ */
