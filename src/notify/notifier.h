#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#include "definitions/constants.h"

class Notifier
{
private:
    /* data */
public:
    Notifier(/* args */);
    virtual ~Notifier();

public:
    void notify(JsonDocument &doc);

};

extern Notifier notifier;

#endif
