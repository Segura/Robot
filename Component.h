#ifndef Component_h
#define Component_h

template<typename T>
class Component
{
public:
    virtual void init(T settings);
    virtual T getSettings();
};

#endif
