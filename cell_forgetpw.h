#ifndef CELL_FORGETPW_H
#define CELL_FORGETPW_H

#include <QDialog>

namespace Ui {
class cell_forgetPW;
}

class cell_forgetPW : public QDialog
{
    Q_OBJECT

public:
    explicit cell_forgetPW(QWidget *parent = nullptr);
    ~cell_forgetPW();

private slots:
    void on_pbtn_confirm_clicked();

private:
    Ui::cell_forgetPW *ui;
};

#endif // CELL_FORGETPW_H
