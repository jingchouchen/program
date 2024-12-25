#include "cell_forgetpw.h"
#include "ui_cell_forgetpw.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug> // 可选，用于调试
#include <QtSql>
cell_forgetPW::cell_forgetPW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cell_forgetPW)
{
    ui->setupUi(this);

    // 连接确认按钮的点击事件到槽函数
    // 设置样式表
        this->setStyleSheet(
            "#frame {"
            "    background-color: #ffffff;"
            "}"
            "#frame_2, #frame_3 {"
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
            "    border-image: url(:/loginIMG/image/pwd.png);"
            "}"
        );


}

cell_forgetPW::~cell_forgetPW()
{
    delete ui;
}

void cell_forgetPW::on_pbtn_confirm_clicked()
{
    QString phone = ui->ledit_phone->text().trimmed();
    QString newPassword = ui->ledit_PW->text();

    // 检查电话号码长度是否为11位
    if (phone.length() != 11) {
        QMessageBox::warning(this, "Invalid Phone Number", "Phone number must be 11 digits.");
        return;
    }

    // 获取数据库连接
    QSqlDatabase db = QSqlDatabase::database(); // 获取在 main.cpp 中创建的数据库连接
    QSqlQuery query(db);

    // 查询数据库，检查是否存在该手机号码
    query.prepare("SELECT * FROM account WHERE phone = :phone");
    query.bindValue(":phone", phone);

    if (!query.exec()) {
        // 查询失败
        QMessageBox::critical(this, "Query Error", "Error executing query: " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        // 如果没有查询到结果，表示手机号码未注册
        QMessageBox::warning(this, "Phone Number Not Registered", "Phone number is not registered.");
        return;
    }

    // 执行更新密码操作
    query.prepare("UPDATE account SET password = :password WHERE phone = :phone");
    query.bindValue(":password", newPassword);
    query.bindValue(":phone", phone);

    if (!query.exec()) {
        // 更新失败
        QMessageBox::critical(this, "Update Error", "Error updating password: " + query.lastError().text());
        return;
    }

    // 修改成功，提示用户
    QMessageBox::information(this, "Password Changed", "Password has been changed successfully.");

    // 清空输入框
    ui->ledit_phone->clear();
    ui->ledit_PW->clear();
}
