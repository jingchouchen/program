#include "cell_register.h"
#include "ui_cell_register.h"
#include <QMessageBox>

cell_register::cell_register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cell_register)
{
    ui->setupUi(this);

    // 设置样式表（保持不变）
    this->setStyleSheet(
        "#frame {"
        "    background-color: #ffffff;"
        "}"
        "#frame_phone, #frame_username,#frame_pwd {"
        "    border: 1px solid #696969;"
        "    border-radius: 5px;"
        "}"
        "QLineEdit {"
        "    border: none;"
        "}"
        "#label {"
        "    border-image: url(:/loginIMG/image/user_name.png);"
        "}"
        "#label_2 {"
        "    border-image: url(:/loginIMG/image/username.png);"
        "}"
        "#label_3 {"
        "    border-image: url(:/loginIMG/image/pwd.png);"
        "}"
    );
}

cell_register::~cell_register()
{
    delete ui;
}

void cell_register::on_pbtn_confirm_clicked()
{
    QString userName = ui->ledit_userName->text().trimmed();
    QString phone = ui->ledit_phone->text().trimmed();
    QString password = ui->ledit_pw1->text();

    // 检查电话号码长度是否为11位
    if (phone.length() != 11) {
        QMessageBox::warning(this, "Invalid Phone Number", "Phone number must be 11 digits.");
        return;
    }

    // 检查用户名和密码是否为空
    if (userName.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Empty Fields", "Please fill in all fields.");
        return;
    }

    // 查询数据库，检查是否已经注册过相同的电话号码
    QSqlQuery query;
    query.prepare("SELECT * FROM account WHERE phone = :phone");
    query.bindValue(":phone", phone);

    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error", "Error executing query.");
        return;
    }

    if (query.next()) {
        // 如果查询到结果，表示手机号码已经注册过
        QMessageBox::warning(this, "Phone Number Exists", "Phone number already registered.");
        return;
    }

    // 如果没有查询到结果，表示可以注册
    query.prepare("INSERT INTO account (phone, user, password) VALUES (:phone, :user, :password)");
    query.bindValue(":phone", phone);
    query.bindValue(":user", userName);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Insert Error", "Error inserting data into database.");
        return;
    }

    // 注册成功，提示用户
    QMessageBox::information(this, "Registration Successful", "Registration successful.");

    // 将手机号码和用户名插入userinfo表
    insertIntoUserInfo(phone, userName);

    // 清空输入框
    ui->ledit_userName->clear();
    ui->ledit_phone->clear();
    ui->ledit_pw1->clear();
}

void cell_register::insertIntoUserInfo(const QString &phone, const QString &userName)
{
    // 执行将手机号码和用户名插入userinfo表的操作
    QSqlQuery query;
    query.prepare("INSERT INTO userinfo (phone, user) VALUES (:phone, :user)");
    query.bindValue(":phone", phone);
    query.bindValue(":user", userName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Insert into UserInfo Error", "Error inserting data into userinfo table.");
        // 可以根据实际情况处理插入失败的情况
    }
}
