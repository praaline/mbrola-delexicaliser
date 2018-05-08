/*
    MBROLA Delexicaliser
    Resynthesiser
    Copyright (c) 2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QDebug>
#include <QString>
#include <QPointer>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>

#include "praaline-core-lite/annotation/IntervalTier.h"
#include "praaline-core-lite/annotation/AnnotationTierGroup.h"
#include "praaline-core-lite/interfaces/praat/PraatPointTierFile.h"
using namespace Praaline::Core;

#include "LanguageDefinition.h"
#include "PseudoLanguage.h"
#include "MBROLAResynthesiser.h"

struct MBROLAResynthesiserData {
    int numberOfPitchTargets;
};

MBROLAResynthesiser::MBROLAResynthesiser() :
    d(new MBROLAResynthesiserData())
{
    d->numberOfPitchTargets = 20;
}

MBROLAResynthesiser::~MBROLAResynthesiser()
{
    delete d;
}

QString MBROLAResynthesiser::createPhoFile(const QString &filenamePho, IntervalTier *tier_phone, const QString &attributePhoneLabels,
                                           const QString &filenamePitchTier)
{
    if (!tier_phone) return "No tier phone";
    // Load pitch data from Praat Pitch Tier file
    QMap<RealTime, double> pitch;
    if (!PraatPointTierFile::load(filenamePitchTier, pitch)) return QString("Error reading pitch tier file: %1").arg(filenamePitchTier);
    // Crete Pho file
    QFile fileOut(filenamePho);
    if (! fileOut.open(QFile::WriteOnly | QFile::Text)) return QString("Error writing file: %1").arg(filenamePho);
    QTextStream out(&fileOut);
    out.setCodec("ISO 8859-1");
    // Write out phones
    foreach(Interval *phone, tier_phone->intervals()) {
        // Phone label
        QString p = (attributePhoneLabels.isEmpty()) ? phone->text() : phone->attribute(attributePhoneLabels).toString();
        if (p.trimmed().isEmpty()) p = "_";
        out << p << "\t";
        // Phone duration
        out << qRound(phone->duration().toDouble() * 1000.0);
        // Pitch targets (percentage of duration - pitch target in Hz)
        if (p != "_") {
            RealTime tStep = phone->duration() / ((double)d->numberOfPitchTargets);
            for (int i = 1; i <= d->numberOfPitchTargets; ++i) {
                RealTime point = phone->tMin() + (tStep * i);
                double pitchTarget = pitch.lowerBound(point).value();
                if (pitchTarget > 50.0 && pitchTarget < 800.0)
                    out << "\t" << i * 5 << "\t" << pitchTarget;
            }
        }
        out << "\n";
    }
    fileOut.close();
    return QString("Created MBROLA pho file: %1").arg(filenamePho);
}
