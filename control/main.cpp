#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <termios.h> // POSIX terminal control definitions
#include <stdint.h>

#define RATE  ((uint8_t) 2)
#define FRAME ((uint8_t) 3)
#define CLEAR ((uint8_t) 4)
#define LINE  ((uint8_t) 5)

int main()
{
	int port = open("/dev/ttyACM1", O_RDWR | O_NOCTTY | O_NDELAY);
	if (port == -1 )
	{
		std::cerr << "Could not open port" << std::endl;
		return 1;
	}
	fcntl(port, F_SETFL,0);
	
	
	
	struct termios port_settings;      // structure to store the port settings inc
	cfsetispeed(&port_settings, B9600);    // set baud rates
	cfsetospeed(&port_settings, B9600);

	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;

	tcsetattr(port, TCSANOW, &port_settings);    // apply the settings to the port
	
	uint8_t data[] = {LINE, 0, 0, 16, 0,FRAME};
	write(port,data,sizeof(data));
	
	return 0;
}
