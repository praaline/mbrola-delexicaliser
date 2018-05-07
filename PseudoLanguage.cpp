#include "praaline-core-lite/annotation/IntervalTier.h"
using namespace Praaline::Core;

#include "PseudoLanguage.h"

struct PseudoLanguageData {
    LanguageDefinition language;
    QStringList allAllowedPhonemes;
};


PseudoLanguage::PseudoLanguage(const LanguageDefinition &language) :
    d(new PseudoLanguageData())
{
    d->language = language;
    // Build an internal list of all allowed phonemes
    foreach (QString phonemeClassName, d->language.phonemeGroupNames()) {
        foreach (QString phoneme, d->language.phonemeGroup(phonemeClassName)) {
            d->allAllowedPhonemes << phoneme;
        }
    }
}

PseudoLanguage::~PseudoLanguage()
{
    delete d;
}

int PseudoLanguage::randInt(int low, int high)
{
    // Returns a random integer value between low and high
    return qrand() % ((high + 1) - low) + low;
}

QString PseudoLanguage::substitutePhoneme(const QString &phoneme, const QString &contextLeft, const QString &contextRight,
                                          const QString &phonemeClassName)
{
    QList<QString> phonemeClass = d->language.phonemeGroup(phonemeClassName);
    int i = 0;
    while (i < 3) {
        QString candidate = phonemeClass.at(randInt(0, phonemeClass.count() - 1));
        QString left = QString("%1 %2").arg(contextLeft).arg(candidate);
        QString right = QString("%1 %2").arg(candidate).arg(contextRight);
        if ((d->language.possibleDiphones().contains(left) || contextLeft == "_") &&
            (d->language.possibleDiphones().contains(right) || contextRight == "_")) {

            if (!(contextLeft == "_" && candidate == "A"))
                return candidate;
        }
        i++;
    }
    if (phoneme.trimmed().isEmpty()) return "_";
    return phoneme;
}

void PseudoLanguage::substitutePhonemes(IntervalTier *tier_phones, const QString &attributeID)
{
    // Substitute phonemes
    for (int i = 1; i < tier_phones->count() - 1; ++i) {
        QString phoneme = tier_phones->interval(i)->text();
        if (phoneme.isEmpty()) phoneme = "_";
        if (!d->allAllowedPhonemes.contains(phoneme))
            phoneme = d->allAllowedPhonemes.at(randInt(0, d->allAllowedPhonemes.count() - 1));

        QString contextLeft = tier_phones->interval(i - 1)->text();
        QString contextRight = tier_phones->interval(i + 1)->text();
        QString substitute = phoneme;

        foreach (QString phonemeClassName, d->language.phonemeGroupNames()) {
            if (d->language.phonemeGroup(phonemeClassName).contains(phoneme)) {
                substitute = substitutePhoneme(phoneme, contextLeft, contextRight, phonemeClassName);
                break;
            }
        }
        if (substitute.isEmpty()) substitute = "_";
        tier_phones->interval(i)->setAttribute(attributeID, substitute);
    }
}
