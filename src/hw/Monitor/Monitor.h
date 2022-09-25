#ifndef __MONITOR_H__
#define __MONITOR_H__
#include <iostream>

class Monitor
{
private:

public:
    Monitor();
    virtual ~Monitor();
    void print(uint8_t *data, int size);
};

#endif /* __MONITOR_H__ */