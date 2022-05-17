#ifndef ICalibratable_h
#define ICalibratable_h

class ICalibratable
{
public:
    virtual void startCalibration();
    virtual void calibrating(int value);
    virtual bool nextCalibrationStep();
    virtual void stopValibrating();
};

#endif
