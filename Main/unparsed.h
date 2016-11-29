#ifndef UNPARSED_H
#define UNPARSED_H

#include <QList>
#include <QRect>
#include <QPoint>
#include <QString>

class Port;

class Unparsed
{
    QString value;

public:
    Unparsed(QString);

    Port asPort();
    QList<int> asArray();
    QList<QPoint> asPointArray();
    QRect asRectangle();
    QString asString();
    int asInt();
    double asDouble();
    bool asBool();
};

#endif // UNPARSED_H
