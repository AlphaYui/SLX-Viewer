#include "pvar.h"

PVar::PVar() : value("")
{
    name = "";
}

PVar::PVar(QString n,QString v) : value(v)
{
    name = n;
}

void PVar::setValue(QString v)
{
    value = Unparsed(v);
}

Unparsed PVar::getValue()
{
    return value;
}

void PVar::setName(QString n)
{
    name = n;
}

QString PVar::getName()
{
    return name;
}
