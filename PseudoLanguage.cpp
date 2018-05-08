/*
    MBROLA Delexicaliser
    Pseudolanguage Generator
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

#include "praaline-core-lite/annotation/IntervalTier.h"
using namespace Praaline::Core;

#include "PseudoLanguage.h"

struct PseudoLanguageData {
    QStringList allAllowedPhonemes;
};


PseudoLanguage::PseudoLanguage() :
    d(new PseudoLanguageData())
{
}

PseudoLanguage::~PseudoLanguage()
{
    delete d;
}

int PseudoLanguage::randInt(int low, int high)
{
    // Returns a random integer value between low and high
    return qrand() % ((high + 1) - low) + low;
}

QString PseudoLanguage::substitutePhoneme(const LanguageDefinition &language,
                                          const QString &phoneme, const QString &contextLeft, const QString &contextRight,
                                          const QString &phonemeClassName)
{
    QList<QString> phonemeClass = language.phonemeGroup(phonemeClassName);
    int i = 0;
    while (i < 5) {
        QString candidate = phonemeClass.at(randInt(0, phonemeClass.count() - 1));
        QString left = QString("%1 %2").arg(contextLeft).arg(candidate);
        QString right = QString("%1 %2").arg(candidate).arg(contextRight);
        if ((language.possibleDiphones().contains(left) || contextLeft == "_") &&
            (language.possibleDiphones().contains(right) || contextRight == "_") &&
            (candidate != contextLeft)) {

            if (!(contextLeft == "_" && candidate == "A"))
                return candidate;
        }
        i++;
    }
    if (phoneme.trimmed().isEmpty()) return "_";
    return phoneme;
}

void PseudoLanguage::substitutePhonemes(const LanguageDefinition &language,
                                        IntervalTier *tier_phones, const QString &attributeID)
{
    // Build an internal list of all allowed phonemes
    d->allAllowedPhonemes.clear();
    foreach (QString phonemeClassName, language.phonemeGroupNames()) {
        foreach (QString phoneme, language.phonemeGroup(phonemeClassName)) {
            d->allAllowedPhonemes << phoneme;
        }
    }
    // Substitute phonemes
    for (int i = 1; i < tier_phones->count() - 1; ++i) {
        QString phoneme = tier_phones->interval(i)->text();
        if (phoneme.isEmpty()) phoneme = "_";
        if (phoneme == "_") continue;

        if (!d->allAllowedPhonemes.contains(phoneme))
            phoneme = d->allAllowedPhonemes.at(randInt(0, d->allAllowedPhonemes.count() - 1));

        QString contextLeft = tier_phones->interval(i - 1)->text();
        QString contextRight = tier_phones->interval(i + 1)->text();
        QString substitute = phoneme;

        foreach (QString phonemeClassName, language.phonemeGroupNames()) {
            if (language.phonemeGroup(phonemeClassName).contains(phoneme)) {
                substitute = substitutePhoneme(language, phoneme, contextLeft, contextRight, phonemeClassName);
                break;
            }
        }
        if (substitute.isEmpty()) substitute = "_";
        if (attributeID.isEmpty())
            tier_phones->interval(i)->setText(substitute);
        else
            tier_phones->interval(i)->setAttribute(attributeID, substitute);
    }
}
