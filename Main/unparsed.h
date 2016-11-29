#ifndef UNPARSED_H
#define UNPARSED_H

#include <QList>
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
    QString asString();
    int asInt();
    double asDouble();
    bool asBool();
};

#endif // UNPARSED_H
