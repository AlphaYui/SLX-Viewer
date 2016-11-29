#ifndef BLOCK_H
#define BLOCK_H

#include "pvar.h"

#include <QString>
#include <QRect>
#include <QMap>
#include <QVariant>

#include <QXmlStreamReader>

class System;

class Block
{
    QString type;
    QString name;
    int SID;

    QRect position;
    int rotation;
    bool mirrored;
    int zOrder;

    QList<PVar*> attr;

    System *subsystem;
    bool hasSubsystem;

    int portsIn;
    int portsOut;

public:
    Block();
    Block(QXmlStreamReader*);

    void read(QXmlStreamReader*);

    void insertAttributes(QXmlStreamAttributes);

    bool isSubsystem(){ return hasSubsystem; }

    QRect dim() { return position; }
    int getSID(){ return SID; }
    QString getName(){ return name; }
    int countOutputPorts(){ return portsOut; }
    int countInputPorts(){ return portsIn; }

    QPoint getPortPosition( bool isOutPort, int portIndex );
};

#endif // BLOCK_H
