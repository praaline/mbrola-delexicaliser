#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

struct MainWindowData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAddFile_triggered();
    void on_actionRemoveFile_triggered();
    void on_actionAddFromFolder_triggered();
    void on_actionDelexicalise_triggered();
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    MainWindowData *d;

    void updateTreeview();
};

#endif // MAINWINDOW_H
