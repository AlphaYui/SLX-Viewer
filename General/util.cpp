#include "util.h"

#include <QtDebug>

/*
 * Skips a specific tag 'tag'
 * Continues reading stream 'in' until the final end tag is found
 *
 * in: The XML input stream
 * tag: The XML-tag to skip
 * return: Whether the end of the stream has been reached (instead of the end tag)
 */
bool skipToTag(QXmlStreamReader* in, QString tag)
{
    // Counts tag instances -> increased with every tag 'tag' entered
    // Has to be zero for the break condition -> toplevel tag left
    int depth = 0;

    // Skips until end of stream or break condition is reached
    while( !in->atEnd() )
    {
        in->readNext();

        if( in->qualifiedName() == tag )
        {
            if( in->isEndElement() )
            {
                if( depth == 0 )
                    break;
                else
                    depth--;
            }
            else if( in->isStartElement() )
            {
                depth++;
            }
        }
    }

    return in->atEnd();
}

/*
 * Converts a QXmlStreamAttribute list 'attr' to a string map
 *
 * attr: The attribute list to convert
 * return: The attributes sorted as strings
 */
QMap<QString,QString> attrListToMap(QXmlStreamAttributes attr)
{
    QMap<QString,QString> result;

    QString key, value;

    // Iterates through attributes and writes them to the map
    for( int i=0; i < attr.length(); i++ )
    {
        key = attr[i].qualifiedName().toString();
        value = attr[i].value().toString();

        result.insert(key,value);
    }

    return result;
}

/*
 * Reads a variable in p-tags from input stream 'in'
 * Format in file: <P Name="VarName">Value</P>
 *
 * in: The XML input stream
 * returns: A general P-Variable that can be interpreted as wished with the as...() methods
 */
PVar* readVariable(QXmlStreamReader *in)
{
    PVar* result = new PVar();

    if( in->qualifiedName() != "P" )
        return result;

    QString name = attrListToMap( in->attributes() ).value("Name");

    in->readNext();
    QString value = in->text().toString();

    result->setName(name);
    result->setValue(value);

    in->readNext();

    return result;
}
