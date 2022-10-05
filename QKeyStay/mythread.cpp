#include "mythread.h"
#include <QThread>
#include <QDebug>

MyThread::MyThread(QObject* parent)
{

}

void MyThread::run()
{
    while (1)
    {
        if (run_type == MOUSE)
        {
            if (pressed)
            {
                Sleep(1000);
                pressed = false;
                if (mouse_button == LEFT)
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0,0);
                else if (mouse_button == RIGHT)
                    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0,0);

            }
            if (stop)
            {
                stop = false;
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0,0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0,0);
            }
        }
        else if (run_type == KEYBOARD)
        {
            if (pressed)
            {
                Sleep(1000);
                pressed = false;
                keybd_event(key, 0, 0, 0);
            }
            if (stop)
            {
                stop = false;
                keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
            }
        }
    }
}
