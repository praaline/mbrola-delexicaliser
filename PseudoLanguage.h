#ifndef PSEUDOLANGUAGE_H
#define PSEUDOLANGUAGE_H

#include <QString>
#include "LanguageDefinition.h"

struct PseudoLanguageData;

namespace Praaline {
namespace Core {
class IntervalTier;
}
}

class PseudoLanguage
{
public:
    PseudoLanguage(const LanguageDefinition &language);
    ~PseudoLanguage();

    void substitutePhonemes(Praaline::Core::IntervalTier *tier_phones, const QString &attributeID);

private:
    PseudoLanguageData *d;

    int randInt(int low, int high);
    QString substitutePhoneme(const QString &phoneme, const QString &contextLeft, const QString &contextRight,
                              const QString &phonemeClassName);

};

#endif // PSEUDOLANGUAGE_H
