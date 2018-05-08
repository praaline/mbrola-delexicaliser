/*
    MBROLA Delexicaliser
    Main GUI
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
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QApplication>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "praaline-core-lite/annotation/AnnotationTierGroup.h"
#include "praaline-core-lite/annotation/IntervalTier.h"
#include "praaline-core-lite/interfaces/praat/PraatTextGrid.h"
using namespace Praaline::Core;

#include "LanguageDefinition.h"
#include "PseudoLanguage.h"
#include "MBROLAResynthesiser.h"

struct MainWindowData {
    QString directory;
    QStringList files;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), d(new MainWindowData)
{
    ui->setupUi(this);
    connect(ui->commandDelexicalise, SIGNAL(clicked(bool)), this, SLOT(on_actionDelexicalise_triggered()));
    // Language definition file default path
    ui->editFilenameLDF->setText(QCoreApplication::applicationDirPath() + "/resources/French.json");
    // Default settings
    ui->editPhoneTier->setText("phone");
    ui->checkDelexicalise->setChecked(true);
    ui->checkSaveDelexicalisedTxg->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d;
}

void MainWindow::updateTreeview()
{
    if (ui->treeviewCorpus->model()) {
        QAbstractItemModel *previous = ui->treeviewCorpus->model();
        ui->treeviewCorpus->setModel(0);
        delete previous;
    }
    if (d->files.isEmpty()) return;
    QStandardItemModel *model = new QStandardItemModel(d->files.count(), 1);
    for (int row = 0; row < d->files.count(); ++row) {
        QStandardItem *item = new QStandardItem(d->files.at(row));
        model->setItem(row, 0, item);
    }
    ui->treeviewCorpus->setModel(model);
}

void MainWindow::on_actionAddFile_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                            tr("Select File(s) to process"),
                            d->directory,
                            tr("Praat TextGrids (*.TextGrid);;Wave Files (*.wav)"),
                            &selectedFilter, options);
    if (fileNames.count() == 0)
        return;
    int i = 0;
    foreach(QString fileNameSelected, fileNames) {
        QFileInfo info(fileNameSelected);
        if (info.suffix().toLower() != "wav" && info.suffix().toLower() != "textgrid" && info.suffix().toLower() != "pitchtier")
            continue;
        QString filename = info.filePath();
        if (filename.length() > info.suffix().length() + 1)
            filename.chop(info.suffix().length() + 1);
        if (!d->files.contains(filename))
            d->files.append(filename);
        i++;
    }
    updateTreeview();
    ui->statusbar->showMessage(QString("Added %1 file(s) for processing.").arg(i), 5000);
}

void MainWindow::on_actionAddFromFolder_triggered()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                tr("Select a folder to process"),
                                d->directory, options);
    if (directory.isEmpty())
        return;
    d->directory = directory;
    // Loop through all files in the input directory and move to the corresponging organised folder if they match the criteria
    QDir dirinfo(directory);
    QFileInfoList list;
    dirinfo.setNameFilters(QStringList() << "*.*");
    list << dirinfo.entryInfoList();
    foreach (QFileInfo info, list) {
        if (info.isDir()) continue;
        if (info.suffix().toLower() != "textgrid") continue;
        QString filename = info.filePath();
        if (filename.length() > info.suffix().length() + 1)
            filename.chop(info.suffix().length() + 1);
        if (!d->files.contains(filename))
            d->files.append(filename);
    }
    updateTreeview();
    ui->statusbar->showMessage("Added files to the corpus from " + directory, 5000);
}

void MainWindow::on_actionRemoveFile_triggered()
{
    if (!ui->treeviewCorpus->model()) return;
    QModelIndex indexSelected = ui->treeviewCorpus->selectionModel()->currentIndex();
    if (!indexSelected.isValid()) return;
    d->files.takeAt(indexSelected.row());
    ui->treeviewCorpus->model()->removeRow(indexSelected.row());
}

void MainWindow::on_actionDelexicalise_triggered()
{
    ui->progressBar->setRange(0, d->files.count());
    ui->progressBar->setValue(0);
    ui->textProgress->clear();
    ui->textProgress->append("Delexicaliser starting...");
    // Open languagee definition file
    LanguageDefinition lang;
    if (!lang.read(ui->editFilenameLDF->text())) {
        QMessageBox::warning(this, "Delexicaliser", "Cannot open language definition file.");
        return;
    }
    // Phones tier
    if (ui->editPhoneTier->text.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Delexicaliser", "Please give the name of the tier containing the phones.");
        return;
    }
    PseudoLanguage pseudo;
    MBROLAResynthesiser resynth;
    foreach (QString filename, d->files) {
        if (!QFile(filename + ".TextGrid").exists()) {
            ui->textProgress->append(QString("Cannot find file: %1").arg(filename + ".TextGrid"));
            continue;
        }
        if (!QFile(filename + ".PitchTier").exists()) {
            ui->textProgress->append(QString("Cannot find file: %1").arg(filename + ".PitchTier"));
            continue;
        }
        AnnotationTierGroup *txg = new AnnotationTierGroup();
        if (!PraatTextGrid::load(filename + ".TextGrid", txg)) {
            ui->textProgress->append(QString("Error reading textgrid: %1").arg(filename + ".TextGrid"));
            delete txg;
            continue;
        }
        IntervalTier *tier_phones = txg->getIntervalTierByName(ui->editPhoneTier->text().trimmed());
        if (!tier_phones) {
            ui->textProgress->append(QString("Cannot read tier %1 in file: %2")
                                     .arg(ui->editPhoneTier->text()).arg(filename + ".TextGrid"));
            delete txg;
            continue;
        }
        if (ui->checkDelexicalise->isChecked()) {
            pseudo.substitutePhonemes(lang, tier_phones, "");
            ui->textProgress->append(QString("Delexicalising in: %1").arg(filename + ".TextGrid"));
        }
        QString mbrolaFilename = QString("%1_delexicalised.pho").arg(filename);
        resynth.createPhoFile(mbrolaFilename, tier_phones, "", filename + ".PitchTier");
        ui->textProgress->append(QString("Writing MBROLA file: %1").arg(mbrolaFilename));
        if (ui->checkSaveDelexicalisedTxg->isChecked()) {
            PraatTextGrid::save(QString("%1_delexicalised.TextGrid").arg(filename), txg);
        }
        delete txg;
        ui->textProgress->append(filename);
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }
    ui->progressBar->setValue(d->files.count());
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
