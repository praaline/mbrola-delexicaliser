#ifndef MBROLARESYNTHESISER_H
#define MBROLARESYNTHESISER_H

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

#include <QString>

namespace Praaline {
namespace Core {
class IntervalTier;
}
}

struct MBROLAResynthesiserData;

class MBROLAResynthesiser
{
public:
    MBROLAResynthesiser();
    ~MBROLAResynthesiser();

    QString createPhoFile(const QString &filenamePho, Praaline::Core::IntervalTier *tier_phone,
                          const QString &attributePhoneLabels, const QString &filenamePitchTier);

private:
    MBROLAResynthesiserData *d;
};

#endif // MBROLARESYNTHESISER_H
