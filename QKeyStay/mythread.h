#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <qt_windows.h>
#include "data.h"


class MyThread  : public QThread
{
public:
    MyThread(QObject* parent = nullptr);
    void run();
};

#endif // MYTHREAD_H
