#include "system.h"

#include "block.h"
#include "wire.h"

#include "General/util.h"

#include <QPainterPath>
#include <QtDebug>

System::System()
{
    blocks = QMap<int,Block*>();
}

System::System(QXmlStreamReader *in)
{
    blocks = QMap<int,Block*>();
    load(in);
}

void System::load(QXmlStreamReader *in)
{
    read(in);
    preloadWires();
}

void System::read(QXmlStreamReader *in)
{
    // Reads system from blockdiagram.xml

    QString currentTag;
    bool isStart = false;

    while( !in->atEnd() )
    {
        in->readNext();

        currentTag = in->qualifiedName().toString();    // Tag type (eg P, Block, System,...)
        isStart = in->isStartElement();                 // Starting tag?

        if( currentTag == "P" )
        {
            // Read and parse p-attribute
            PVar *var = readVariable(in);
            this->attr.push_back(var);

            // If it's a location, parse and insert it
            if( var->getName() == "Location" )
            {
                position = strToRect(var->getValue().asString());
            }
        }
        else if( currentTag == "Object" && isStart )
        {
            // Object tags are most probably useless and therefore skipped
            skipToTag(in, "Object");
        }
        else if( currentTag == "Block" && isStart )
        {
            // Reads and parses Block tag

            Block *b = new Block(in);

            // Adds block to subsystem list if required
            if( b->isSubsystem() )
                subsystems.push_back(b);

            blocks.insert(b->getSID(), b);
        }
        else if( currentTag == "Line" && isStart )
        {
            // Reads and parses Block tag

            Wire *w = new Wire(in);
            wires.push_back(w);
        }
        else if( currentTag == "System" && in->isEndElement() ) // Leaves current system
            break;

        /*
            Note: Subsystems are read in the according blocks
        */
    }

    if( in->hasError() )
    {
        // TODO: Error handling
        // Only top level?
    }
}

void System::preloadWires()
{
    for( int i=0; i < wires.size(); ++i )
    {
        wires[i]->preloadLines(&blocks);
    }
}

QPixmap System::render()
{
    // Early rendering prototype
    // Iterates through all blocks and paints their position rectangle

    QPixmap map( position.width(), position.height() );

    QPainter p(&map);
    QPainterPath path;

    QFont font("Arial");
    font.setPixelSize(12);
    //p.setFont(font);

    p.fillRect(map.rect(),QColor(255,255,255));
    p.setPen(QColor(0,0,0));

    Block *b;
    int blockCount = blocks.size();
    QList<int> blockKeys = blocks.keys();
    QRect blockDim;

    QPoint textPosition;
    int textX;
    int textY;

    QString blockName;

    for( int i=0; i < blockCount; ++i )
    {
        b = blocks[blockKeys.at(i)];
        blockDim = b->dim();

        if( blockDim.width() > 0 && blockDim.height()> 0)
        {
            textX = blockDim.x();
            textY = blockDim.y() + blockDim.height() + 15;
            textPosition.setX(textX);
            textPosition.setY(textY);

            blockName = b->getName();

            /*p.drawRect( rect );
            p.drawText(QPoint(rect.x(), rect.y()+rect.height()+15),b->getName());*/
            path.addRect(blockDim);
            //path.addText(textPosition, font,blockName);
        }
    }

    p.drawPath(path);

    QVector<QLine> lines;

    for( int i=0; i < wires.size(); ++i )
    {
        lines = wires[i]->generateLines(&blocks);

        p.drawLines(lines);
    }

    return map;
}
