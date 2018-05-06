#ifndef PRAATTEXTGRID_H
#define PRAATTEXTGRID_H

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

#include "pncore_global.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include "base/RealTime.h"
#include "annotation/AnnotationTierGroup.h"
#include "annotation/AnnotationTier.h"
#include "annotation/IntervalTier.h"
#include "annotation/PointTier.h"
#include "PraatTextFile.h"

namespace Praaline {
namespace Core {

class PRAALINE_CORE_SHARED_EXPORT PraatTierData
{
public:
    QString name;
    QString type;
    int itemsCount;
};

class PRAALINE_CORE_SHARED_EXPORT PraatTextGrid : PraatTextFile
{
public:
    // Public static methods to read and write textgrids
    static bool load(const QString &filename, AnnotationTierGroup *data);
    static bool save(const QString &filename, AnnotationTierGroup *data);

    static QList<PraatTierData> getTierData(const QString &filename);

protected:
    // IO Functions
    static bool readTierHeader(bool isShortFile, QTextStream &stream, QString &line,
                               int &tierType, int &tierSize, QString &name, double &xMin, double &xMax);
    static bool readInterval(bool isShortFile, QTextStream &stream, QString &line,
                             double &xMin, double &xMax, QString &text);
    static bool readPoint(bool isShortFile, QTextStream &stream, QString &line,
                          double &timePoint, QString &text);

private:
    static QRegularExpression regex_interval_tier;
    static QRegularExpression regex_point_tier;
    static QRegularExpression regex_name;
    static QRegularExpression regex_size;
    static QRegularExpression regex_xmin;
    static QRegularExpression regex_xmax;
    static QRegularExpression regex_interval;
    static QRegularExpression regex_point;
    static QRegularExpression regex_text;
    static QRegularExpression regex_time;
    static QRegularExpression regex_mark;

    static QRegularExpression regex_short_interval_tier;
    static QRegularExpression regex_short_point_tier;
    static QRegularExpression regex_short_name;
    static QRegularExpression regex_short_size;
    static QRegularExpression regex_short_xmin;
    static QRegularExpression regex_short_xmax;
    static QRegularExpression regex_short_text;
    static QRegularExpression regex_short_time;
    static QRegularExpression regex_short_mark;
};

} // namespace Core
} // namespace Praaline

#endif // PRAATTEXTGRID_H
