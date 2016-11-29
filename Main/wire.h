#ifndef WIRE_H
#define WIRE_H

#include <QLine>
#include <QList>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>

#include "port.h"
#include "system.h"
#include "block.h"

class Wire
{
    QString name;

    QList<QPoint> points;

    Port src;   // Start
    Port dst;   // End destination

    QList<Wire> branches;
    bool isBranch;

    bool preloadedLines;
    QVector<QLine> lines;

public:
    Wire();
    Wire(QXmlStreamReader *in);
    Wire(QXmlStreamReader *in, bool isBranch);

    void read(QXmlStreamReader *in);

    QVector<QLine> generateLines(QMap<int,Block*>* mapSID);
    QVector<QLine> generateLines(QMap<int,Block*>* mapSID, QPoint start);

    void preloadLines(QMap<int,Block*>* mapSID);
};

#endif // WIRE_H
