#include <QDir>
#include <QFile>
#include <QTextStream>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LanguageDefinition.h"
#include "PseudoLanguage.h"
#include "MBROLAResynthesiser.h"

#include "praaline-core-lite/annotation/AnnotationTierGroup.h"
#include "praaline-core-lite/annotation/IntervalTier.h"
#include "praaline-core-lite/interfaces/praat/PraatTextGrid.h"
using namespace Praaline::Core;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LanguageDefinition langdef;
    langdef.read(QDir::homePath() + "/Develop/mbrola-delexicaliser/resources/French.json");

    QString path = QDir::homePath() + "/Develop/mbrola-delexicaliser/example/";

    AnnotationTierGroup *txg = new AnnotationTierGroup();
    PraatTextGrid::load(path + "rhapsodie_political.TextGrid", txg);
    IntervalTier *tier_phone = txg->getIntervalTierByName("phone");
    PseudoLanguage pseudo;
    pseudo.substitutePhonemes(langdef, tier_phone, "");
    MBROLAResynthesiser resynth;
    resynth.createPhoFile(path + "rhapsodie_political.pho", tier_phone, "", path + "rhapsodie_political.PitchTier");

    // def.write(QDir::homePath() + "/Develop/mbrola-delexicaliser/resources/test.json");
    int i = 6;
}

MainWindow::~MainWindow()
{
    delete ui;
}
