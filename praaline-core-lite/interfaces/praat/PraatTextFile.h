#ifndef PRAATTEXTFILE_H
#define PRAATTEXTFILE_H

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
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include "interfaces/InterfaceTextFile.h"

namespace Praaline {
namespace Core {

class PRAALINE_CORE_SHARED_EXPORT PraatTextFile : InterfaceTextFile
{
protected:
    PraatTextFile() {}
    virtual ~PraatTextFile() {}

    static void detectEncoding(QFile &file, QTextStream &stream);
    static QString seekPattern(QTextStream &stream, const QRegularExpression &regex);
};

} // namespace Core
} // namespace Praaline

#endif // PRAATTEXTFILE_H
