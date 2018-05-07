#ifndef LANGUAGEDEFINITION_H
#define LANGUAGEDEFINITION_H

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
