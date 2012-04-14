#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <termios.h> // POSIX terminal control definitions
#include <stdint.h>
#include <unistd.h>

#define RATE  ((uint8_t) 2)
#define FRAME ((uint8_t) 3)
#define CLEAR ((uint8_t) 4)
#define LINE  ((uint8_t) 5)
#define BOX   ((uint8_t) 6)

int setup(const char* device);

class Display
{
	int port;
public:
	Display(int port) : port(port) {}
	void frame()
	{
		uint8_t data[] = {FRAME, 0};
		write(port, data, 2);
	};
	void clear()
	{
		uint8_t data[] = {CLEAR, 0};
		write(port, data, 2);
	}
	void line(int x1, int y1, int x2, int y2)
	{
		uint8_t data[] = {LINE, x1, y1, x2, y2};
		write(port, data, 5);
	}
	void box(int x1, int y1, int x2, int y2)
	{
		uint8_t data[] = {BOX, x1, y1, x2, y2};
		write(port, data, 5);
	}
};


int main()
{
	// Init serial
	int port = setup("/dev/ttyACM1");
	if (port == -1 )
	{
		std::cerr << "Could not open port" << std::endl;
		return 1;
	}
	Display display(port);
	
	for (uint8_t i = 1; i < 8*4; ++i)
	{
		display.clear();
		display.box(0, 0, 32 - 1, 8 - 1);
		display.line(1, 4, i, 4);
		display.frame();
		sleep(1);
	}
	
	return 0;
}

int setup(const char* device)
{
	// Init serial
	int port = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (port == -1 ) return port;
	
	fcntl(port, F_SETFL,0);
	struct termios port_settings;      // structure to store the port settings inc
	cfsetispeed(&port_settings, B9600);    // set baud rates
	cfsetospeed(&port_settings, B9600);
	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;
	tcsetattr(port, TCSANOW, &port_settings);    // apply the settings to the port
	
	return port;
}

