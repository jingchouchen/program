#ifndef CELL_USERINFORMATION_H
#define CELL_USERINFORMATION_H

#include <QDialog>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QRegularExpressionValidator>
#include <QBuffer>
#include "cell_login.h"

namespace Ui {
class cell_userInformation;
}

class cell_userInformation : public QDialog
{
    Q_OBJECT

public:
    explicit cell_userInformation(QWidget *parent = nullptr);
    ~cell_userInformation();

private slots:
    void on_pushButton_reSelect_clicked();
    void on_pushButton_savePhoto_clicked();
    void on_pushButton_save_clicked();
    void on_anyFieldChanged();
    void on_pushButton_quit_clicked();

private:
    Ui::cell_userInformation *ui;
    QPixmap currentImage;
    bool imageChanged;

    void loadData(const QString &phoneNumber);
    bool isValidEmail(const QString &email);
};

#endif // CELL_USERINFORMATION_H
