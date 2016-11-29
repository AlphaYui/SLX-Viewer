#include "util.h"

#include <QtDebug>

bool skipToTag(QXmlStreamReader* in, QString tag)
{
    int i = 0;
    int depth = 0;

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

        i++;
    }

    qDebug() << "Skipped " << i << " elements";

    return in->atEnd();
}

QMap<QString,QString> attrListToMap(QXmlStreamAttributes attr)
{
    QMap<QString,QString> result;

    QString key, value;

    for( int i=0; i < attr.length(); i++ )
    {
        key = attr[i].qualifiedName().toString();
        value = attr[i].value().toString();

        result.insert(key,value);
    }

    return result;
}

// P Variables only
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

QList<int> strToArray(QString str)
{
    QList<int> result;

    int prev = 1;
    int index = -1;
    QString cut;

    while( (index = str.indexOf(',',prev)) != -1 )
    {
        cut = str.mid(prev, index-prev);


        prev = index + 2;

        result.push_back(cut.toInt());
    }

    cut = str.mid(prev);
    cut.remove(']');

    result.push_back(cut.toInt());
    return result;
}

QRect strToRect(QString str)
{
    QRect result;

    QList<int> arr = strToArray(str);

    if( arr.length() > 3 )
        result = QRect(arr[0],arr[1],arr[2]-arr[0],arr[3]-arr[1]);

    return result;
}
