/*
 * display.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include "display.h"
#include "ht1632c.h"
#include <util/delay_basic.h>
#include <string.h>
#include <stdlib.h>

Display::Display(): buffer(HTleds) {
    ::HTpinsetup();
    ::HTsetup();
}

void Display::update() {
    HTsendscreen();
}

void Display::clear() {
    ::memset(buffer, 0, 32);
}

void Display::line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
// Taken from http://www.edepot.com/linec.html

	bool yLonger=false;
	int incrementVal, endVal;

	int shortLen=y2-y1;
	int longLen=x2-x1;
	if (abs(shortLen)>abs(longLen)) {
		int swap=shortLen;
		shortLen=longLen;
		longLen=swap;
		yLonger=true;
	}
	
	endVal=longLen;
	if (longLen<0) {
		incrementVal=-1;
		longLen=-longLen;
	} else incrementVal=1;

	double decInc;
	if (longLen==0) decInc=(double)shortLen;
	else decInc=((double)shortLen/(double)longLen);
	double j=0.0;
	if (yLonger) {
		for (int i=0;i!=endVal;i+=incrementVal) {
			pixelOn(x1+(int)j,y1+i);
			j+=decInc;
		}
	} else {
		for (int i=0;i!=endVal;i+=incrementVal) {
			pixelOn(x1+i,y1+(int)j);
			j+=decInc;
		}
	}
}

void Display::box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	for (uint8_t x = x1; x < x2; ++x)
	{
		pixelOn(x, y1);
		pixelOn(x, y2);
	}
	for (uint8_t y = y1; y < y2; ++y)
	{
		pixelOn(x1, y);
		pixelOn(x2, y);
	}
}



