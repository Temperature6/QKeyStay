#include "mainwindow.h"
#include "ui_mainwindow.h"



DWORD mouseKey;
DWORD keyboardKey;
HHOOK KBDhook;
HHOOK MOUhook;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*启动子线程*/
    t->start();
    /*Json配置读取*/
    QJsonObject config;
    QJsonArray items;

    QFile file("config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString config_str = file.readAll();
    file.close();
    //判断错误
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(config_str.toUtf8(),&parseJsonErr);
    if(parseJsonErr.error == QJsonParseError::NoError)
    {
        config = document.object();
        sc_stop_str = config["Stop"].toString();
        sc_keyboard_str = config["Keyboard"].toString();
        sc_mouse_str = config["Mouse"].toString();
    }

    /*窗口初始化*/
    setWindowOpacity(0.0);
    move(0, 0);
    resize(10, 10);
    /*托盘图标初始化*/
    tray->setIcon(QIcon(":pic\\logo.png"));
    tray->setToolTip("QKeyStay");
    tray->show();
    /*全局快捷键*/
    QxtGlobalShortcut *sc_mouse = new QxtGlobalShortcut(this);
    sc_mouse->setShortcut(QKeySequence(sc_mouse_str));
    QxtGlobalShortcut *sc_keyboard = new QxtGlobalShortcut(this);
    sc_keyboard->setShortcut(QKeySequence(sc_keyboard_str));
    QxtGlobalShortcut *sc_stop = new QxtGlobalShortcut(this);
    sc_stop->setShortcut(QKeySequence(sc_stop_str));
    /*链接信号和槽*/
    connect(sc_keyboard, &QxtGlobalShortcut::activated, this, &MainWindow::RegKeyBoardHook);
    connect(sc_mouse, &QxtGlobalShortcut::activated, this, &MainWindow::RegMouseHook);
    connect(sc_stop, &QxtGlobalShortcut::activated, this, &MainWindow::Stop);
    connect(tray, &QSystemTrayIcon::activated, this, &MainWindow::TrayActivied);
}

MainWindow::~MainWindow()
{
    tray->hide();
    tray->destroyed();
    delete ui;
}

void MainWindow::RegKeyBoardHook()
{
    UnhookWindowsHookEx(MOUhook);
    UnhookWindowsHookEx(KBDhook);
    key = 0;
    tray->showMessage("QKeyStay", "已按下第一组快捷键, 等待按下键盘按键...", QIcon(":pic\\keyboard.png"));
    KBDhook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
}

void MainWindow::RegMouseHook()
{
    UnhookWindowsHookEx(MOUhook);
    UnhookWindowsHookEx(KBDhook);
    mouse_button = Null;
    tray->showMessage("QKeyStay", "已按下第一组快捷键, 等待按下鼠标按键...", QIcon(":pic\\mouse.png"));
    MOUhook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, 0, 0);
}

void MainWindow::Stop()
{
    stop = true;
    tray->showMessage("QKeyStay", "停止按下按键", QIcon(":pic\\stop.png"));
}

void MainWindow::TrayActivied(QSystemTrayIcon::ActivationReason Ac_code)
{
    switch (Ac_code)
    {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        break;
    case QSystemTrayIcon::Context:
        TrayRightClick();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    case QSystemTrayIcon::Unknown:
        break;
    }
}

void MainWindow::TrayRightClick()
{
    QMenu* menu = new QMenu(this);
    QAction* exit_ac = new QAction("退出", this);
    exit_ac->setIcon(QIcon(":/pic/close.png"));
    menu->addAction(exit_ac);
    connect(exit_ac, &QAction::triggered, this, &MainWindow::close);
    tray->setContextMenu(menu);
    menu->exec( QCursor::pos());
    delete menu;delete exit_ac;
    return;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
            case WM_KEYDOWN:
                run_type = KEYBOARD;
                pressed = true;
                key = PKBDLLHOOKSTRUCT(lParam)->vkCode;
                UnhookWindowsHookEx(KBDhook);
            break;
            case WM_KEYUP:

            break;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
            case WM_RBUTTONDOWN:
                run_type = MOUSE;
                pressed = true;
                mouse_button = RIGHT;
                UnhookWindowsHookEx(MOUhook);
            break;
            case WM_LBUTTONDOWN:
                run_type = MOUSE;
                pressed = true;
                mouse_button = LEFT;
                UnhookWindowsHookEx(MOUhook);
            break;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


