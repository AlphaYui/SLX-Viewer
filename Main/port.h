#ifndef PORT_H
#define PORT_H

#include <QString>

class Port
{
public:
    static const int UNDEFINED = 0;
    static const int IN = 1;
    static const int OUT = 2;
    static const int BRANCH = 3;

private:
    int type;   // IN or OUT port
    int SID;    // SID of belonging block
    int index;  // Index of port at block

public:
    Port();
    Port(int t,int s,int i);

    int getType(){ return type; }
    int getSID(){ return SID; }
    int getPortIndex(){ return index; }
    bool isValid(){ return (type!=UNDEFINED); }
};

#endif // PORT_H
