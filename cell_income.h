#ifndef CELL_INCOME_H
#define CELL_INCOME_H

#include <QWidget>

namespace Ui {
class Cell_income;
}

class Cell_income : public QWidget
{
    Q_OBJECT

public:
    explicit Cell_income(QWidget *parent = nullptr);
    ~Cell_income();
    void setData(const QString &money, const QString &type, const QString &remarks, const QString &date);

private slots:
    void on_pbtn_confirm_clicked();
    void on_pbtn_cancel_clicked();

private:
    Ui::Cell_income *ui;
    QString oldMoney;
    QString oldType;
    QString oldRemarks;
    QString oldDate;
};

#endif // CELL_INCOME_H
