#include "Calibrator.h"

Calibrator::Calibrator(ICalibratable* components,
                       ezLED *statusLed,
                       void (*onFinish)())
{
    this->components = components;
    this->statusLed = statusLed;
    this->onFinish = onFinish;
}

void Calibrator::start()
{
    this->currentComponent = 0;
    this->statusLed->blinkNumberOfTimes(500, 500, 3);
}

void Calibrator::loop(int value, bool nextPending)
{
    ICalibratable *component = this->components[this->currentComponent];
    component->calibrating(value);
    if (nextPending)
    {
        if (component->nextCalibrationStep())
        {
            this->statusLed->blinkNumberOfTimes(500, 500, 2);
        }
        else
        {
            if (this->currentComponent == COMPONENTS_COUNT - 1)
            {
                this->statusLed->blinkNumberOfTimes(500, 500, 3);
                this->onFinish();
            }
            else
            {
                this->currentComponent++;
            }
        }
    }
}
