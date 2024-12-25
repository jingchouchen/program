#include "cell_login.h"
#include "ui_cell_login.h"
#include "mainwindow.h" // 假设这是你的主窗口头文件

#include <QMessageBox>
#include <QSqlQuery>
#include <QIcon>

QString cell_login::phoneNumber = "";

cell_login::cell_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cell_login),
    keepSignIn(false) // 初始化勾选框状态为未勾选
{
    ui->setupUi(this);

    // 加载保存的账号和密码
        loadSavedCredentials();
        // 连接勾选框状态改变的信号和槽
            connect(ui->chk_keepSignIn, &QCheckBox::stateChanged, this, &cell_login::on_chk_keepSignIn_stateChanged);
    // 设置样式表
        this->setStyleSheet(
            "#frame {"
            "    background-color: #ffffff;"
            "}"
            "#frame_user, #frame_pwd {"
            "    border: 1px solid #696969;"
            "    border-radius: 5px;"
            "}"
            "QLineEdit {"
            "    border: none;"
            "}"
            "/* 按钮-忘记密码 */"
            "#btn_forgetPWD {"
            "    border: none;"
            "    color: #e83737;"
            "}"
            "/* 按钮-忘记密码-鼠标悬停 */"
            "#btn_forgetPWD:hover {"
            "    border: none;"
            "    color: #e83737;"
            "}"
            "/* 按钮-登录 */"
            "btn_signIn {"
            "    background-color: #e67e22;"  // 橘色背景
            "    color: white;"  // 白色文字
            "    border: 1px solid #e67e22;"  // 橘色边框
            "    border-radius: 5px;"  // 圆角
            "    padding: 5px 10px;"  // 内边距
            "    font-size: 14px;"  // 文字大小
            "}"
            "btn_signIn:hover {"
            "    background-color: #d35400;"  // 鼠标悬停时的颜色
            "}"
            "btn_signIn:pressed {"
            "    background-color: #a04000;"  // 鼠标按下时的颜色
            "}"
            "#label_2 {"
            "    border-image: url(:/loginIMG/image/user_name.png);"
            "}"
            "#label_3 {"
            "    border-image: url(:/loginIMG/image/pwd.png);"
            "}"
        );


}

cell_login::~cell_login()
{
    delete ui;
}


void cell_login::on_btn_signIn_clicked()
{
    QString phone = ui->ledit_User->text().trimmed();
    QString password = ui->ledit_PWS->text();

    // 检查电话号码长度是否为11位
    if (phone.length() != 11) {
        QMessageBox::warning(this, "Invalid Phone Number", "Phone number must be 11 digits.");
        return;
    }

    // 查询数据库，检查是否已经注册过相同的电话号码和密码（区分大小写）
    QSqlQuery query;
    query.prepare("SELECT * FROM account WHERE phone = :phone AND BINARY password = :password");
    query.bindValue(":phone", phone);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error", "Error executing query.");
        return;
    }

    if (!query.next()) {
        // 如果没有查询到结果，表示手机号码或密码错误
        QMessageBox::warning(this, "Login Failed", "Phone number or password incorrect.");
        return;
    }

    // 登录成功，保存手机号码
    savePhoneNumber(phone);

    // 如果勾选了记住账号和密码，保存账号和密码到配置中
    if (keepSignIn) {
        saveCredentials(phone, password);
    }

    // 登录成功，关闭登录窗口并打开主窗口
    QMessageBox::information(this, "Login Successful", "Login successful.");
    emit loginSuccess();

    MainWindow *m_mainwindow = new MainWindow();
    m_mainwindow->show();

    this->close(); // 关闭登录窗口
}

void cell_login::savePhoneNumber(const QString &phone)
{
    phoneNumber = phone;
}

QString cell_login::getPhoneNumber()
{
    return phoneNumber;
}

void cell_login::loadSavedCredentials()
{
    QSettings settings("MyCompany", "MyApp"); // 创建一个配置对象，使用你的公司名和应用名
    QString savedPhone = settings.value("Login/Phone").toString();
    QString savedPassword = settings.value("Login/Password").toString();

    if (!savedPhone.isEmpty() && !savedPassword.isEmpty()) {
        ui->ledit_User->setText(savedPhone);
        ui->ledit_PWS->setText(savedPassword);
        ui->chk_keepSignIn->setChecked(true);
        keepSignIn = true;
    }
}

void cell_login::saveCredentials(const QString &phone, const QString &password)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("Login/Phone", phone);
    settings.setValue("Login/Password", password);
}

void cell_login::on_chk_keepSignIn_stateChanged(int state)
{
    if (state == Qt::Checked) {
        keepSignIn = true;
    } else {
        keepSignIn = false;
        // 如果取消勾选，清除保存的账号和密码
        QSettings settings("MyCompany", "MyApp");
        settings.remove("Login/Phone");
        settings.remove("Login/Password");
    }
}
