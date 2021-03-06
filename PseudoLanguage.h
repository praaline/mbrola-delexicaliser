#ifndef PSEUDOLANGUAGE_H
#define PSEUDOLANGUAGE_H

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

#include <QString>
#include "LanguageDefinition.h"

struct PseudoLanguageData;

namespace Praaline {
namespace Core {
class IntervalTier;
}
}

class PseudoLanguage
{
public:
    PseudoLanguage();
    ~PseudoLanguage();

    void substitutePhonemes(const LanguageDefinition &language,
                            Praaline::Core::IntervalTier *tier_phones, const QString &attributeID);

private:
    PseudoLanguageData *d;

    int randInt(int low, int high);
    QString substitutePhoneme(const LanguageDefinition &language,
                              const QString &phoneme, const QString &contextLeft, const QString &contextRight,
                              const QString &phonemeClassName);

};

#endif // PSEUDOLANGUAGE_H
