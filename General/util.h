#ifndef UTIL_H
#define UTIL_H

#include "Main/pvar.h"

#include <QList>
#include <QMap>
#include <QRect>
#include <QVector2D>
#include <QXmlStreamReader>

/* A set of utility functions */
/* Those may be resorted in the future */

/* XML parsing utilities */
bool skipToTag(QXmlStreamReader* in, QString tag);
QMap<QString,QString> attrListToMap(QXmlStreamAttributes);
PVar* readVariable(QXmlStreamReader* in);

#endif // UTIL_H
