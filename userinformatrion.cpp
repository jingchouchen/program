#include "userinformatrion.h"
#include "ui_userinformatrion.h"

userInformatrion::userInformatrion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userInformatrion)
{
    ui->setupUi(this);
}

userInformatrion::~userInformatrion()
{
    delete ui;
}
