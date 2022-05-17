#ifndef Calibrator_h
#define Calibrator_h

#include <ezLED.h>
#include "ICalibratable.h"

#define COMPONENTS_COUNT 1

class Calibrator
{
public:
    Calibrator(ICalibratable* components,
               ezLED* statusLed,
               void (*onFinish)());
    void start();
    void loop(int value, bool nextPending);

private:
    int currentComponent;
    ezLED* statusLed;
    ICalibratable* components[COMPONENTS_COUNT];
    void (*onFinish)();
};

#endif
