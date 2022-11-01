#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>

class Calculation : public QObject
{
    Q_OBJECT
public:
    explicit Calculation(int taskNumber = 0);
    void run();

signals:
    void sentProgress(int taskNumber, int percent);
    void finished(int taskNumber);
    void started(int taskNumber);

private:
    int taskNumber;
    int coef;
};

#endif // CALCULATION_H
