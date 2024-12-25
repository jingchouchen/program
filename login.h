#ifndef LOGIN_H
#define LOGIN_H

#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include "cell_login.h"
#include "cell_register.h"
#include "cell_forgetpw.h"
#include "mainwindow.h" // 包含主窗口头文件

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    void initPage(); // 用于登录界面各个功能界面的转换
private slots:
    void onLoginSuccess(); // 声明登录成功的槽函数

private:
    Ui::login *ui;
    cell_login *m_loginPage;
    cell_register *m_registerPage;
    cell_forgetPW *m_forgetPWPage;
    MainWindow *m_mainwindow; // 声明一个主窗口对象
};

#endif // LOGIN_H

