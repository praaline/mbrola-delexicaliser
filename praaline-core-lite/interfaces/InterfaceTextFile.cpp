#include <QString>
#include <QByteArray>
#include <QTextStream>
#include "InterfaceTextFile.h"

/*
    Praaline - Core module - Interfaces
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

namespace Praaline {
namespace Core {

// QString InterfaceTextFile::m_defaultEncoding = "UTF-8";
// or
QString InterfaceTextFile::m_defaultEncoding = "ISO 8859-1";

InterfaceTextFile::InterfaceTextFile()
{
}

InterfaceTextFile::~InterfaceTextFile()
{
}

void InterfaceTextFile::setDefaultEncoding(const QString &encoding)
{
    m_defaultEncoding = encoding;
}

QString InterfaceTextFile::defaultEncoding()
{
    return m_defaultEncoding;
}

void InterfaceTextFile::detectEncoding(QFile &file, QTextStream &stream)
{
    // Encoding detection
    QByteArray fileHeaderHex = file.peek(4).toHex();
    char *fileHeaderChar = fileHeaderHex.data();
    QString fileBOM;
    for(int i = 0; i < fileHeaderHex.size(); i++) {
        fileBOM += fileHeaderChar[i];
    }
    stream.setAutoDetectUnicode(true);
    if(fileBOM.left(6) == "efbbbf") {
        stream.setCodec("UTF-8");
    }
    else if(fileBOM.left(4) == "feff") {
        stream.setCodec("UTF-16BE");
    }
    else if(fileBOM.left(4) == "fffe") {
        stream.setCodec("UTF-16LE");
    }
    else if(fileBOM.left(8) == "0000feff") {
        stream.setCodec("UTF-32BE");
    }
    else if(fileBOM.left(8) == "fffe0000") {
        stream.setCodec("UTF-32LE");
    }
    else {
        stream.setCodec(m_defaultEncoding.toLatin1().constData());
    }
}

} // namespace Core
} // namespace Praaline
