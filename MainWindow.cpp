#include <QDir>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LanguageDefinition.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LanguageDefinition def;
    def.read(QDir::homePath() + "/Develop/mbrola-delexicaliser/resources/French.json");
    // def.write(QDir::homePath() + "/Develop/mbrola-delexicaliser/resources/test.json");
    int i = 6;
}

MainWindow::~MainWindow()
{
    delete ui;
}
