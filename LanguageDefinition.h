#ifndef LANGUAGEDEFINITION_H
#define LANGUAGEDEFINITION_H

/*
    MBROLA Delexicaliser
    Language Definition File
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
#include <QStringList>
#include <QMap>

struct LanguageDefinitionData;

class LanguageDefinition
{
public:
    LanguageDefinition();
    ~LanguageDefinition();

    bool read(const QString &filename);
    bool write(const QString &filename) const;

    QString language() const;
    QString phoneset() const;
    QList<QString> phonemeGroupNames() const;
    QStringList phonemeGroup(const QString &phonemeGroupName) const;
    QStringList possibleDiphones() const;

private:
    LanguageDefinitionData *d;
};

#endif // LANGUAGEDEFINITION_H
