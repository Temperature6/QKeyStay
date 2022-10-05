#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <qxtglobalshortcut.h>
#include <QSystemTrayIcon>
#include <qt_windows.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include "mythread.h"
#include "data.h"


namespace Ui {
class MainWindow;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam); //低级键盘钩子
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam); //低级鼠标钩子

extern bool pressed;
extern bool stop;
extern DWORD mouseKey;
extern DWORD keyboardKey;
extern HHOOK KBDhook;
extern HHOOK MOUhook;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Var
    QSystemTrayIcon* tray = new QSystemTrayIcon(this);
    //QThread *press_th = new QThread();
    QString sc_mouse_str = "Alt+M";
    QString sc_keyboard_str = "Alt+K";
    QString sc_stop_str = "Ctrl+Shift+S";
    //Func
    MyThread *t = new MyThread();

    void RegMouseHook();
    void RegKeyBoardHook();
    void Stop();
    void TrayActivied(QSystemTrayIcon::ActivationReason Ac_code);
    void TrayRightClick();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
