#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "screenshot.h"
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionPrint_triggered();
private:
    Ui::MainWindow *ui;
    Screenshot* mScreenshot;
};

#endif // MAINWINDOW_H
