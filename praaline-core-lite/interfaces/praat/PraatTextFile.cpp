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

#include <QString>
#include <QTextStream>
#include <QRegularExpression>
#include "PraatTextFile.h"

namespace Praaline {
namespace Core {

void PraatTextFile::detectEncoding(QFile &file, QTextStream &stream)
{
    InterfaceTextFile::detectEncoding(file, stream);
}

QString PraatTextFile::seekPattern(QTextStream &stream, const QRegularExpression &regex)
{
    QString line = QString();
    QRegularExpressionMatch match;
    while (!match.hasMatch() && ! stream.atEnd()) {
        line += stream.readLine();
        match = regex.match(line);
    }
    if (match.hasMatch())
        return match.captured(1);
    return QString();
}

} // namespace Core
} // namespace Praaline
