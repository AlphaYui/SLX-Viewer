#include "block.h"

#include "system.h"
#include "General/util.h"

#include <QtDebug>

Block::Block()
{
    rotation = 0;
    portsOut = 1;
    portsIn = 1;

    hasSubsystem = false;
}

Block::Block(QXmlStreamReader *in)
{
    rotation = 0;
    portsOut = 1;
    portsIn = 1;

    hasSubsystem = false;
    read(in);
}

void Block::read(QXmlStreamReader *in)
{
    // Read in-tag attributes
    QXmlStreamAttributes attr = in->attributes();
    insertAttributes(attr);

    QString atName;

    while( !in->atEnd() )
    {
        in->readNext();

        atName = in->qualifiedName().toString();

        // Read and parse p-attributes
        if( atName == "P" )
        {
            PVar* var = readVariable(in);
            this->attr.push_back(var);

            if( var->getName() == "Position" )
            {
                // If it's a position, parse and insert it
                position = var->getValue().asRectangle();
            }
            else if( var->getName() == "Ports" )
            {
                QList<int> ports = var->getValue().asArray();

                if( ports.length() > 0 )
                    portsIn = ports[0];

                if( ports.length() > 1 )
                    portsOut = ports[1];
            }
            else if( var->getName() == "BlockRotation" )
            {
                rotation += var->getValue().asInt();
            }
            else if( var->getName() == "BlockMirror" )
            {
                mirrored = var->getValue().asBool();
                if(mirrored)
                    rotation += 180;
            }
        }
        else if( atName == "System" )
        {
            // Read subsystem
            System *s = new System(in);
            subsystem = s;
            hasSubsystem = true;
        }
        else if( atName == "Block" && in->isEndElement() )   // Leave loop when end tag is found
            break;
    }
}

void Block::insertAttributes(QXmlStreamAttributes attr)
{
    // Automatically detects and sets important attributes
    QString atName;

    for( int i = 0; i < attr.length(); ++i )
    {
        atName = attr[i].qualifiedName().toString();

        if( atName == "BlockType" )
        {
            type = attr[i].value().toString();
        }
        else if( atName == "SID" )
        {
            SID = attr[i].value().toInt();
        }
        else if( atName == "Name" )
        {
            name = attr[i].value().toString();
        }
    }
}

QPoint Block::getPortPosition(bool isOutPort, int portIndex)
{
    int x = position.x();
    int y = position.y();

    if( rotation%360 == 0 )
    {
        // Input left, Output right
        if( isOutPort )
        {
            x += (position.width());
            y += ((portIndex-0.5) * position.height() / portsOut);
        }
        else
        {
            y += ((portIndex-0.5) * position.height() / portsIn);
        }
    }
    else if( (rotation+90)%360 == 0 )
    {
        // Input bottom, Output top
        if( isOutPort )
        {
            x += ((portIndex-0.5) * position.width() / portsOut);
        }
        else
        {
            x += ((portIndex-0.5) * position.width() / portsIn);
            y += (position.height());
        }
    }
    else if( (rotation+180)%360 == 0 )
    {
        // Input right, Output left
        if( isOutPort )
        {
            y += ((portIndex-0.5) * position.height() / portsOut);
        }
        else
        {
            x += (position.width());
            y += ((portIndex-0.5) * position.height() / portsIn);
        }
    }
    else if( (rotation+270)%360 == 0 )
    {
        // Input top, Output bottom
        if( isOutPort )
        {
            x += ((portIndex-0.5) * position.width() / portsOut);
            y += (position.height());
        }
        else
        {
            x += ((portIndex-0.5) * position.width() / portsIn);
        }
    }

    return QPoint(x,y);
}
