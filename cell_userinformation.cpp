#include "cell_userInformation.h"
#include "ui_cell_userInformation.h"
#include <QDateTime>
#include <QRegularExpression>

cell_userInformation::cell_userInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cell_userInformation),
    imageChanged(false)
{
    ui->setupUi(this);

    // 设置电子邮件输入的正则表达式验证器
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(emailRegex, this);
    ui->lineEdit_mail->setValidator(emailValidator);

    // 设置初始图片
    if (!currentImage.load(":/mainwindow/image/noPhoto.png")) {
        ui->label_image->setText("No Photo");
    } else {
        ui->label_image->setPixmap(currentImage.scaled(ui->label_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // 加载数据
    QString phoneNumber = cell_login::getPhoneNumber(); // 获取电话号码
    loadData(phoneNumber);

    // 连接信号槽
    //connect(ui->pushButton_reSelect, &QPushButton::clicked, this, &cell_userInformation::on_pushButton_reSelect_clicked);
    //connect(ui->pushButton_savePhoto, &QPushButton::clicked, this, &cell_userInformation::on_pushButton_savePhoto_clicked);
    //connect(ui->pushButton_save, &QPushButton::clicked, this, &cell_userInformation::on_pushButton_save_clicked);
    connect(ui->lineEdit_user, &QLineEdit::textChanged, this, &cell_userInformation::on_anyFieldChanged);
    connect(ui->comboBox_gender, &QComboBox::currentTextChanged, this, &cell_userInformation::on_anyFieldChanged);
    connect(ui->dateEdit_birthday, &QDateEdit::dateChanged, this, &cell_userInformation::on_anyFieldChanged);
    connect(ui->lineEdit_city, &QLineEdit::textChanged, this, &cell_userInformation::on_anyFieldChanged);
    connect(ui->lineEdit_mail, &QLineEdit::textChanged, this, &cell_userInformation::on_anyFieldChanged);
    connect(ui->plainTextEdit_description, &QPlainTextEdit::textChanged, this, &cell_userInformation::on_anyFieldChanged);

    // 设置初始保存按钮状态
    ui->pushButton_savePhoto->setEnabled(false);
    ui->pushButton_save->setEnabled(false);

    // 设置样式表
        this->setStyleSheet(
                "#frame {"
                "    border-image: url(:/loginIMG/image/background-4.png);"
                "}"
                "#frame_photo {"
                "    border-image: url(:/loginIMG/image/background-4.png);"
                "}"
                "#frame_other {"
                "    border-image: url(:/loginIMG/image/background-4.png);"
                "}"
                "#frame_head {"
                "    border: 1px solid #696969;"
                "    border-radius: 5px;"
                 "    background-color: #ffffff;"
                "}"
                "#label_image {"
                "    border: none;"
                "}"
        );
}

cell_userInformation::~cell_userInformation()
{
    delete ui;
}

void cell_userInformation::loadData(const QString &phoneNumber)
{
    // 从数据库加载数据
    QSqlQuery query;
    query.prepare("SELECT user, gender, birthdate, city, email, description, image FROM userinfo WHERE phone = :phone");
    query.bindValue(":phone", phoneNumber);

    if (query.exec() && query.next()) {
        ui->lineEdit_user->setText(query.value("user").toString());
        ui->comboBox_gender->setCurrentText(query.value("gender").toString());
        ui->dateEdit_birthday->setDate(query.value("birthdate").toDate().isValid() ? query.value("birthdate").toDate() : QDate::currentDate());
        ui->lineEdit_city->setText(query.value("city").toString());
        ui->lineEdit_mail->setText(query.value("email").toString());
        ui->plainTextEdit_description->setPlainText(query.value("description").toString());

        QString imagePath = query.value("image").toString();
        if (!imagePath.isEmpty() && currentImage.load(imagePath)) {
            ui->label_image->setPixmap(currentImage.scaled(ui->label_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            currentImage.load(":/mainwindow/image/noPhoto.png");
            ui->label_image->setPixmap(currentImage.scaled(ui->label_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        QMessageBox::warning(this, "未找到", "找不到该电话号码对应的用户信息。");
    }
}

void cell_userInformation::on_pushButton_reSelect_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择图片", "", "图片 (*.png *.jpg *.jpeg *.bmp)");
    if (!filePath.isEmpty()) {
        currentImage.load(filePath);
        ui->label_image->setPixmap(currentImage.scaled(ui->label_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageChanged = true;
        ui->pushButton_savePhoto->setEnabled(true);
    }
}

void cell_userInformation::on_pushButton_savePhoto_clicked()
{
    if (imageChanged) {
        QString savePath = "user_image.png"; // 可以修改为合适的路径
        if (!currentImage.save(savePath)) {
            QMessageBox::critical(this, "保存错误", "保存图片失败。");
            return;
        }

        // 更新数据库中的图片路径
        QSqlQuery query;
        query.prepare("UPDATE userinfo SET image = :image WHERE phone = :phone");
        query.bindValue(":image", savePath);
        query.bindValue(":phone", cell_login::getPhoneNumber()); // 获取电话号码

        if (!query.exec()) {
            QMessageBox::critical(this, "数据库错误", "更新数据库中的图片失败。");
            return;
        }

        imageChanged = false;
        ui->pushButton_savePhoto->setEnabled(false);
        QMessageBox::information(this, "保存成功", "成功保存图片。");
    }
}

void cell_userInformation::on_pushButton_save_clicked()
{
    QString user = ui->lineEdit_user->text().trimmed();
    QString gender = ui->comboBox_gender->currentText();
    QString birthdate = ui->dateEdit_birthday->date().toString("yyyy-MM-dd");
    QString city = ui->lineEdit_city->text().trimmed();
    QString email = ui->lineEdit_mail->text().trimmed();
    QString description = ui->plainTextEdit_description->toPlainText().trimmed();

    if (user.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名不能为空。");
        return;
    }

    if (!isValidEmail(email)) {
        QMessageBox::warning(this, "输入错误", "电子邮件格式无效。");
        return;
    }

    // 更新数据库中的用户信息
    QSqlQuery query;
    query.prepare("UPDATE userinfo SET user = :user, gender = :gender, birthdate = :birthdate, city = :city, email = :email, description = :description WHERE phone = :phone");
    query.bindValue(":user", user);
    query.bindValue(":gender", gender);
    query.bindValue(":birthdate", birthdate);
    query.bindValue(":city", city);
    query.bindValue(":email", email);
    query.bindValue(":description", description);
    query.bindValue(":phone", cell_login::getPhoneNumber()); // 获取电话号码

    if (!query.exec()) {
        QMessageBox::critical(this, "数据库错误", "无法更新数据库中的用户信息。");
        return;
    }

    ui->pushButton_save->setEnabled(false);
    QMessageBox::information(this, "保存成功", "用户信息已成功保存。");
}

void cell_userInformation::on_anyFieldChanged()
{
    ui->pushButton_save->setEnabled(true);
}

bool cell_userInformation::isValidEmail(const QString &email)
{
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");
    QRegularExpressionMatch match = emailRegex.match(email);
    return match.hasMatch();
}

void cell_userInformation::on_pushButton_quit_clicked()
{
    if (ui->pushButton_save->isEnabled()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "未保存的更改", "数据还未保存，是否要保存?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            // 保存数据
            on_pushButton_save_clicked();
            close();
        } else if (reply == QMessageBox::No) {
            // 不保存，直接退出
            close();
        }
        // 如果 reply 是 QMessageBox::Cancel，什么都不做，不退出
    } else {
        // 没有未保存的更改，直接退出
        close();
    }
}
