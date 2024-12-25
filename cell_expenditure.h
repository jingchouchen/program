#ifndef CELL_EXPENDITURE_H
#define CELL_EXPENDITURE_H

#include <QWidget>

namespace Ui {
class cell_expenditure;
}

class cell_expenditure : public QWidget
{
    Q_OBJECT

public:
    explicit cell_expenditure(QWidget *parent = nullptr);
    ~cell_expenditure();
    void setData(const QString &money, const QString &type, const QString &remarks, const QString &date);

private slots:
    void on_pbtn_confirm_clicked();
    void on_pbtn_cancel_clicked();

private:
    Ui::cell_expenditure *ui;
    QString oldMoney;
    QString oldType;
    QString oldRemarks;
    QString oldDate;

};

#endif // CELL_EXPENDITURE_H
