#include "cell_expenditure.h"
#include "ui_cell_expenditure.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "cell_login.h"
#include <QDateTime> // Include QDateTime header
cell_expenditure::cell_expenditure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cell_expenditure)
{
    ui->setupUi(this);
     ui->dedit_time->setDateTime(QDateTime::currentDateTime()); // Set dedit_time to current date and time
}

cell_expenditure::~cell_expenditure()
{
    delete ui;
}
void cell_expenditure::setData(const QString &money, const QString &type, const QString &remarks, const QString &date)
{
    oldMoney = money;
    oldType = type;
    oldRemarks = remarks;
    oldDate = date;

    ui->dsbx_account->setValue(money.toDouble());
    ui->cbx_type->setCurrentText(type);
    ui->edit_remarks->setPlainText(remarks);
    ui->dedit_time->setDateTime(QDateTime::fromString(date, "yyyy-MM-dd hh:mm:ss"));
}

void cell_expenditure::on_pbtn_confirm_clicked()
{
    QString type = ui->cbx_type->currentText(); // 获取选择的收入类型
    QString amountStr = ui->dsbx_account->text(); // 获取输入的金额
    QString timeStr = ui->dedit_time->dateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取选择的时间并格式化为字符串
    QString remarks = ui->edit_remarks->toPlainText(); // 获取备注信息
    QString phoneNumber = cell_login::getPhoneNumber(); // 获取手机号

    // 数据验证
    if (type.isEmpty() || amountStr.isEmpty() || timeStr.isEmpty()) {
        QMessageBox::critical(this, "错误", "收入类型、金额和时间不能为空！");
        return;
    }

    bool ok;
    double amount = amountStr.toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::critical(this, "错误", "金额输入无效！");
        return;
    }

    QSqlQuery query;
    if (oldMoney.isEmpty() && oldType.isEmpty() && oldRemarks.isEmpty() && oldDate.isEmpty()) {
        // 执行数据库插入操作
        query.prepare("INSERT INTO expenditure (money, typee, remarks, date, phone) "
                      "VALUES (:money, :typee, :remarks, :date, :phone)");
    } else {
        // 执行数据库更新操作
        query.prepare("UPDATE expenditure SET money = :money, typee = :typee, remarks = :remarks, date = :date "
                      "WHERE phone = :phone AND money = :oldMoney AND typee = :oldType AND remarks = :oldRemarks AND date = :oldDate");
        query.bindValue(":oldMoney", oldMoney);
        query.bindValue(":oldType", oldType);
        query.bindValue(":oldRemarks", oldRemarks);
        query.bindValue(":oldDate", oldDate);
    }
    query.bindValue(":money", amount);
    query.bindValue(":typee", type);
    query.bindValue(":remarks", remarks);
    query.bindValue(":date", timeStr);
    query.bindValue(":phone", phoneNumber);

    if (!query.exec()) {
        qDebug() << "插入或更新收入记录失败：" << query.lastError().text();
        QMessageBox::critical(this, "数据库错误", "无法添加或更新收入记录：" + query.lastError().text());
    } else {
        qDebug() << "插入或更新收入记录成功";
        QMessageBox::information(this, "成功", "添加或更新收入记录成功！");
        // 清空输入框
        ui->dsbx_account->clear();
        ui->edit_remarks->clear();
        // 返回上一级窗口或执行其他操作
        this->close(); // 关闭当前窗口
    }
}

void cell_expenditure::on_pbtn_cancel_clicked()
{
    this->close();
}
