#include "display.h"
#include "runner.h"
#include "serialrunner.h"

int main(void)
{
	Display display(0,0);
	Runner runner(display);
	SerialRunner serialRunner(runner);

	display.line(0,0,31,16);
	display.line(31,0,0,16);
	display.update();
	while (1)
	{
		serialRunner.run();
	}

	return(0);
}
