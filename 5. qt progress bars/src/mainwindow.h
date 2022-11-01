#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "calculation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void runThreads();

signals:
    void startCalculation(int taskNumber, int coef);

public slots:
    void on_pBarValueChanged(int taskNumber, int value);
    void on_pBarFinished(int taskNumber);
    void on_pushButton_clicked();
    void on_anyTaskStarted();

private:
    Ui::MainWindow *ui;
    int finishedCount = 0;

};
#endif // MAINWINDOW_H
