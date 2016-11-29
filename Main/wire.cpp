#include "wire.h"

#include "pvar.h"
#include "General/util.h"

#include <cmath>

Wire::Wire()
{
    preloadedLines = false;
}

Wire::Wire(QXmlStreamReader *in)
{
    preloadedLines = false;
    read(in);
}

Wire::Wire(QXmlStreamReader *in, bool isBranch)
{
    preloadedLines = false;
    this->isBranch = isBranch;

    read(in);
}

void Wire::read(QXmlStreamReader *in)
{
    QString currentTag;
    bool isStart;

    while(!in->atEnd())
    {
        in->readNext();

        currentTag = in->qualifiedName().toString();
        isStart = in->isStartElement();

        if( currentTag == "P" && isStart )
        {
            // Reads and parses p-attributes
            PVar* var = readVariable(in);

            if(var->getName() == "Points")
                points = var->getValue().asPointArray();

            if(var->getName() == "Src")
                src = var->getValue().asPort();

            if(var->getName() == "Dst")
                dst = var->getValue().asPort();

            if(var->getName() == "Name")
                name = var->getValue().asString();
        }
        else if( currentTag == "Branch" && isStart )
        {
            // Reads and parses sub-wires (== branches)

            Wire w(in, true);
            branches.push_back(w);
        }
        else if( (currentTag == "Line" || currentTag == "Branch") && in->isEndElement() )
            break;  // End element -> break loop
    }
}

QVector<QLine> Wire::generateLines(QMap<int, Block*> *mapSID)
{
    if(preloadedLines)
        return lines;

    Block* srcBlock = mapSID->value(src.getSID());

    // Calculates starting position of the output block
    QPoint start = srcBlock->getPortPosition(true, src.getPortIndex());

    return generateLines(mapSID, start);
}

QVector<QLine> Wire::generateLines(QMap<int, Block*> *mapSID, QPoint start)
{
    if(preloadedLines)
        return lines;

    QVector<QLine> result;

    Block* dstBlock = mapSID->value(dst.getSID());

    QPoint prev = start;
    QPoint now;

    // Iterates through waypoints
    for( int i=0; i < points.length(); ++i )
    {
        now = prev + points[i];

        result.push_back( QLine(prev,now) );

        prev = now;
    }

    // Iterates through branches
    for( int i=0; i < branches.length(); ++i )
    {
        result += (branches[i].generateLines(mapSID, prev)); // Evtl. falsche Verwendung von +=
    }

    // Connects to right port at destination block
    if( dst.isValid() )
    {
        now = dstBlock->getPortPosition(false, dst.getPortIndex());

        result.push_back( QLine(prev,now) );
    }

    return result;
}

void Wire::preloadLines(QMap<int, Block *> *mapSID)
{
    lines = generateLines(mapSID);
    preloadedLines = true;
}
