#ifndef LANGUAGEDEFINITION_H
#define LANGUAGEDEFINITION_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QJsonDocument>

struct LanguageDefinitionData;

class LanguageDefinition
{
public:
    LanguageDefinition();
    ~LanguageDefinition();

    void read(const QJsonDocument &json);
    void write(QJsonDocument &json) const;

    QString language() const;
    QString phoneset() const;
    QList<QString> phonemeGroupNames() const;
    QStringList phonemeGroup(const QString &phonemeGroupName) const;
    QStringList possibleDiphones() const;

private:
    LanguageDefinitionData *d;
};

#endif // LANGUAGEDEFINITION_H
