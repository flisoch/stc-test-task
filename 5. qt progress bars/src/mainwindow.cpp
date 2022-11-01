#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include "calculation.h"

void initProgressBars(Ui::MainWindow* mainWindow) {
    QList<QProgressBar*> pbs = mainWindow->verticalLayoutWidget->findChildren<QProgressBar*>();
    foreach (QProgressBar* pb, pbs) {
        pb->setValue(0);
        pb->setStyleSheet("");
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initProgressBars(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pBarValueChanged(int taskNumber, int value)
{
    QString pbName = QString("progressBar_") + QString::number(taskNumber);
    QProgressBar* pb = ui->verticalLayoutWidget->findChild<QProgressBar*>(pbName);
    pb->setValue(value);
    QApplication::processEvents();
}


void MainWindow::on_pBarFinished(int taskNumber)
{
    QString pbName = QString("progressBar_") + QString::number(taskNumber);
    QProgressBar* pb = ui->verticalLayoutWidget->findChild<QProgressBar*>(pbName);
    pb->setValue(100);
    pb->setStyleSheet("QProgressBar {text-align: middle; } QProgressBar::chunk {background-color: green;}");
    finishedCount++;
    if (finishedCount == 10) {
        ui->pushButton->setText("Restart");
        finishedCount = 0;
    }
    QApplication::processEvents();
}



void MainWindow::on_pushButton_clicked()
{
    initProgressBars(ui);

    for(int i = 0; i < 10; i++) {

        QThread * thread = new QThread();
        Calculation* c = new Calculation(i);

        connect(thread, &QThread::started, c, &Calculation::run);
        connect(c,&Calculation::started, this, &MainWindow::on_anyTaskStarted);
        connect(c,&Calculation::finished,thread,&QThread::quit);
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);
        connect(c,&Calculation::finished, this, &MainWindow::on_pBarFinished);
        connect(c,&Calculation::sentProgress, this, &MainWindow::on_pBarValueChanged);


        thread->start();
    }
    qInfo() << "Running Main thread: " << QThread::currentThread();

}

void MainWindow::on_anyTaskStarted()
{
    ui->pushButton->setText("Stop");
}

