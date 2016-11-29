#ifndef SYSTEM_H
#define SYSTEM_H

#include <QList>
#include <QMap>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QVariant>
#include <QVector>

#include <QXmlStreamReader>

#include "pvar.h"

class Block;
class Wire;

class System
{
    QList<Block*> subsystems;
    QMap<int,Block*> blocks;    // SID <--> Block
    QList<Wire*> wires;

    QList<PVar*> attr;

    QRect position;

    void read( QXmlStreamReader* );
    void preloadWires();

public:
    System();
    System( QXmlStreamReader* );

    void load( QXmlStreamReader* );



    QPixmap render();
};

#endif // SYSTEM_H
