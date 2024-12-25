#ifndef CELL_LOGIN_H
#define CELL_LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings> // 添加这个头文件用来保存配置
namespace Ui {
class cell_login;
}

class cell_login : public QDialog
{
    Q_OBJECT
signals:
    void loginSuccess(); // 定义登录成功信号
public:
    explicit cell_login(QWidget *parent = nullptr);
    ~cell_login();

 static QString getPhoneNumber(); // 静态成员函数，用于获取手机号码

private slots:
    void on_btn_signIn_clicked();
void on_chk_keepSignIn_stateChanged(int state); // 新增勾选框状态改变的槽函数

private:
    Ui::cell_login *ui;
    QIcon iconShow;
    QIcon iconHide;

    static QString phoneNumber; // 静态成员变量，用于保存手机号码

       void savePhoneNumber(const QString &phone); // 保存手机号码的函数
       bool keepSignIn; // 用来保存勾选框的状态

          void loadSavedCredentials(); // 加载保存的账号和密码
          void saveCredentials(const QString &phone, const QString &password); // 保存账号和密码
};

#endif // CELL_LOGIN_H
