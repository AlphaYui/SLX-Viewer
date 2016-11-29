#include "unparsed.h"

#include "port.h"

Unparsed::Unparsed(QString str)
{
    value = str;
}

QString Unparsed::asString()
{
    return value;
}

int Unparsed::asInt()
{
    return value.toInt();
}

double Unparsed::asDouble()
{
    return value.toDouble();
}

bool Unparsed::asBool()
{
    QString comp = value.toLower();

    if( comp == "true" || comp == "on" )
        return true;
    else if( comp == "false" || comp == "off" )
        return false;
    else if( value.toDouble() != 0 )
        return true;

    return false;
}

QList<int> Unparsed::asArray()
{
    QList<int> result;

    int prev = 1;
    int index = -1;
    QString cut;

    while( (index = value.indexOf(',',prev)) != -1 )
    {
        cut = value.mid(prev, index-prev);

        prev = index + 2;

        result.push_back(cut.toInt());
    }

    cut = value.mid(prev);
    cut.remove(']');

    result.push_back(cut.toInt());

    return result;
}

QList<QPoint> Unparsed::asPointArray()
{
    QList<QPoint> result;

    int prev = 1;
    int xIndex = -1;    // ,
    int yIndex = -1;    // ;
    QString cutX, cutY;
    QPoint p;

    while( (xIndex = value.indexOf(',',prev)) != -1 && (yIndex = value.indexOf(';',xIndex+2)) != -1 )
    {
        cutX = value.mid(prev,xIndex-prev);
        cutY = value.mid(xIndex+2,yIndex-xIndex-2);

        p = QPoint(cutX.toInt(), cutY.toInt());

        prev = yIndex + 2;
        result.push_back(p);
    }

    xIndex = value.indexOf(',',prev);
    cutX = value.mid(prev,xIndex-prev);
    cutY = value.mid(xIndex+2);
    cutY.remove(']');

    result.push_back(QPoint(cutX.toInt(), cutY.toInt()));

    return result;
}

QRect Unparsed::asRectangle()
{
    QList<int> arr = asArray();

    if( arr.length() > 3 )
        return QRect(arr[0],arr[1],arr[2],arr[3]);
    else
        return QRect();
}

Port Unparsed::asPort()
{
    // 23#in:1
    int iSID = value.indexOf('#');
    int iType = value.indexOf(':');

    int SID = value.left(iSID).toInt();

    QString strType = value.mid(iSID+1, iType-iSID-1);
    int type;

    if( strType == "in" )
        type = Port::IN;
    else if( strType == "out" )
        type = Port::OUT;
    else
        type = Port::UNDEFINED;

    int index = value.mid(iType+1).toInt();

    return Port(type,SID,index);
}
