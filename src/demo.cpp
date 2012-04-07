#include "display.h"
#include "runner.h"
#include "serialrunner.h"

int main(void) {

    Display display;
    Runner runner(display);
    SerialRunner serialRunner(runner);

	display.line(0,0,32,8);
	display.update();
    while (1)
        serialRunner.run();

    return(0);
}
