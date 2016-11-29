#ifndef PVAR_H
#define PVAR_H

#include <QMap>
#include <QString>
#include <QVariant>

#include "unparsed.h"

class PVar
{
    Unparsed value;
    QString name;

public:
    PVar();
    PVar(QString,QString);

    QString getName();
    void setName(QString);

    Unparsed getValue();
    void setValue(QString);
};

#endif // PVAR_H
