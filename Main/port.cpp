#include "port.h"

Port::Port()
{
    type = UNDEFINED;
    SID = -1;
    index = -1;
}

Port::Port(int t,int s,int i)
{
    type = t;
    SID = s;
    index = i;
}
