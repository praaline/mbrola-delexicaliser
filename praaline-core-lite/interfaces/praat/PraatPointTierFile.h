#ifndef PRAATPOINTTIERFILE_H
#define PRAATPOINTTIERFILE_H

/*
    Praaline - Core module - Interfaces - Praat
    Copyright (c) 2011-2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QObject>
#include <QPair>
#include <QString>
#include <QList>
#include <QMap>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include "base/RealTime.h"
#include "PraatTextFile.h"

namespace Praaline {
namespace Core {

class PRAALINE_CORE_SHARED_EXPORT PraatPointTierFile : PraatTextFile
{
public:
    // Public static methods to read and write point tier files (e.g. pitch tier, intensity tier)
    static bool load(const QString &filename, QMap<RealTime, double> &points);
    static bool save(const QString &filename,  const QString &praatObjectClass,
                     QMap<RealTime, double> &points);

private:
    static bool readPoint(bool isShortFile, QTextStream &stream, QString &line,
                          double &timePoint, double &value);
    PraatPointTierFile() {}
};

} // namespace Core
} // namespace Praaline

#endif // PRAATPOINTTIERFILE_H
