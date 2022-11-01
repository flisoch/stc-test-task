#include "calculation.h"
#include <QDebug>
#include <iostream>
#include <QThread>
#include <QApplication>

Calculation::Calculation(int taskNumber) : QObject(nullptr)
{
     this->taskNumber = taskNumber;
     this->coef = qrand() % 800000;
}

void Calculation::run() {
    qInfo() << "Running Worker in thread: " << QThread::currentThread();

    emit started(taskNumber);
    for (int i = 0; i < coef; i++) {
        float progress = (float)(i+1) / coef * 100;
        if ((int)progress == 100) {
            emit finished(taskNumber);
            break;
        }
        emit sentProgress(taskNumber, (int)progress);

    }
}
