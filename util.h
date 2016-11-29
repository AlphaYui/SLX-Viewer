#ifndef UTIL_H
#define UTIL_H

#include "pvar.h"

#include <QList>
#include <QMap>
#include <QRect>
#include <QVector2D>
#include <QXmlStreamReader>

bool skipToTag(QXmlStreamReader* in, QString tag);
QMap<QString,QString> attrListToMap(QXmlStreamAttributes);
PVar* readVariable(QXmlStreamReader* in);

QList<int> strToArray(QString str);
QRect strToRect(QString str);

#endif // UTIL_H
