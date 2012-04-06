#include "display.h"
#include "effects/hscroll.h"
#include "runner.h"
#include "serialrunner.h"
#include "fonts/jiffy.h"

int main(void) {

    Display display;
    Runner runner(display);
    SerialRunner serialRunner(runner);

    while (1)
        serialRunner.run();

    return(0);
}
