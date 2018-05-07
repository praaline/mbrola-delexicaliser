#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

bool LanguageDefinition::read(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonLanguage = jsonDoc.object();
    // Header: language name and phoneme-set name
    if (jsonLanguage.contains("language") && jsonLanguage["language"].isString())
        d->language = jsonLanguage["language"].toString();
    if (jsonLanguage.contains("phoneset") && jsonLanguage["phoneset"].isString())
        d->phoneset = jsonLanguage["phoneset"].toString();
    // Phoneme groups array
    d->phonemeGroups.clear();
    if (jsonLanguage.contains("phoneme_groups") && jsonLanguage["phoneme_groups"].isArray()) {
        QJsonArray phonemeGroupsArray = jsonLanguage["phoneme_groups"].toArray();
        for (int phonemeGroupIndex = 0; phonemeGroupIndex < phonemeGroupsArray.size(); ++phonemeGroupIndex) {
            QJsonObject jsonPhonemeGroup = phonemeGroupsArray[phonemeGroupIndex].toObject();
            QString phonemeGroupName; QStringList phonemeGroupContents;
            if (jsonPhonemeGroup.contains("name") && jsonPhonemeGroup["name"].isString())
                phonemeGroupName = jsonPhonemeGroup["name"].toString();
            if (jsonPhonemeGroup.contains("phonemes") && jsonPhonemeGroup["phonemes"].isArray()) {
                QJsonArray jsonPhonemesArray = jsonPhonemeGroup["phonemes"].toArray();
                for (int phonemeIndex = 0; phonemeIndex < jsonPhonemesArray.size(); ++phonemeIndex) {
                    phonemeGroupContents << jsonPhonemesArray.at(phonemeIndex).toString();
                }
            }
            if ((!phonemeGroupName.isEmpty()) && (!phonemeGroupContents.isEmpty()))
                d->phonemeGroups.insert(phonemeGroupName, phonemeGroupContents);
        }
    }
    // Possible diphones array
    d->possibleDiphones.clear();
    if (jsonLanguage.contains("possible_diphones") && jsonLanguage["possible_diphones"].isArray()) {
        QJsonArray jsonPossibleDiphonesArray = jsonLanguage["possible_diphones"].toArray();
        for (int diphoneIndex = 0; diphoneIndex < jsonPossibleDiphonesArray.size(); ++diphoneIndex) {
            d->possibleDiphones << jsonPossibleDiphonesArray.at(diphoneIndex).toString();
        }
    }
    return true;
}

bool LanguageDefinition::write(const QString &filename) const
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QJsonObject jsonLanguage;
    // Header
    jsonLanguage["language"] = d->language;
    jsonLanguage["phoneset"] = d->phoneset;
    // Phonme groups
    QJsonArray jsonPhonemeGroupsArray;
    foreach (QString phonemeGroupName, d->phonemeGroups.keys()) {
        QJsonObject jsonPhonemeGroup;
        jsonPhonemeGroup["name"] = phonemeGroupName;
        QJsonArray jsonPhonemesArray;
        foreach (QString phoneme, d->phonemeGroups.value(phonemeGroupName)) {
            jsonPhonemesArray.append(QJsonValue(phoneme));
        }
        jsonPhonemeGroup["phonemes"] = jsonPhonemesArray;
        jsonPhonemeGroupsArray.append(jsonPhonemeGroup);
    }
    jsonLanguage["phoneme_groups"] = jsonPhonemeGroupsArray;
    // Possible diphones array
    QJsonArray jsonPossibleDiphonesArray;
    jsonLanguage["possible_diphones"] = jsonPossibleDiphonesArray;
    // Write out JSON document
    QJsonDocument jsonDoc(jsonLanguage);
    file.write(jsonDoc.toJson());
    return true;
}

