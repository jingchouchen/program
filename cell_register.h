#ifndef CELL_REGISTER_H
#define CELL_REGISTER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class cell_register;
}

class cell_register : public QDialog
{
    Q_OBJECT

public:
    explicit cell_register(QWidget *parent = nullptr);
    ~cell_register();

private slots:
    void on_pbtn_confirm_clicked(); // 槽函数，处理确认按钮点击事件

private:
    Ui::cell_register *ui;
void insertIntoUserInfo(const QString &phone, const QString &userName);
};

#endif // CELL_REGISTER_H
