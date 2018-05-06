#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>


#include "LanguageDefinition.h"

struct LanguageDefinitionData {
    QString language;
    QString phoneset;
    QMap<QString, QStringList> phonemeGroups;
    QStringList possibleDiphones;
};

LanguageDefinition::LanguageDefinition() :
    d(new LanguageDefinitionData)
{
}

LanguageDefinition::~LanguageDefinition()
{
    delete d;
}

QString LanguageDefinition::language() const
{
    return d->language;
}

QString LanguageDefinition::phoneset() const
{
    return d->phoneset;
}

QList<QString> LanguageDefinition::phonemeGroupNames() const
{
    return d->phonemeGroups.keys();
}

QStringList LanguageDefinition::phonemeGroup(const QString &phonemeGroupName) const
{
    return d->phonemeGroups.value(phonemeGroupName);
}

QStringList LanguageDefinition::possibleDiphones() const
{
    return d->possibleDiphones;
}

void LanguageDefinition::read(const QJsonDocument &json)
{

    // Language definition
//    if (json.contains("language") && json["language"].isString())
//        d->language = json["language"].toString();
//    if (json.contains("phoneset") && json["phoneset"].isString())
//        d->phoneset = json["phoneset"].toString();

}

void LanguageDefinition::write(QJsonDocument &json) const
{

//    json["language"] = d->language;
//    json["phoneset"] = d->phoneset;

}

