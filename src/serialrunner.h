/*
 * serialrunner.h
 *
 *  Created on: 23/03/2012
 *      Author: michael
 */

#ifndef SERIALRUNNER_H_
#define SERIALRUNNER_H_

#include <stdint.h>
#include "runner.h"

class SerialRunner {
private:
    Runner& runner;
public:
    SerialRunner(Runner& runner);
    void run();
};

#endif /* SERIALRUNNER_H_ */
