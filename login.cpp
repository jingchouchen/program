#include "login.h"
#include "./ui_login.h"
#include <QPushButton>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
    , m_loginPage(new cell_login(this))
    , m_registerPage(new cell_register(this))
    , m_forgetPWPage(new cell_forgetPW(this))
    , m_mainwindow(new MainWindow()) // 初始化主窗口对象
{
    ui->setupUi(this);
    initPage();
    connect(m_loginPage, &cell_login::loginSuccess, this, &login::onLoginSuccess);
    this->setStyleSheet(
        "#frame_background {"
        "    border-image: url(:/loginIMG/image/background-4.png);"
        "}"

        /*登录背景*/
        "#frame_login {"
        "    border-image: url(:/loginIMG/image/green.png);"
        "}"
        /*右侧图片*/
        "#frame_right {"
        "    border-image: url(:/loginIMG/image/anyother.png);"
        "}"
    );

}

login::~login()
{
    delete ui;
    delete m_loginPage;
    delete m_registerPage;
    delete m_forgetPWPage;
    delete m_mainwindow; // 删除主窗口对象
}

void login::initPage()
{
    // Add the widgets to the stackedWidget
    ui->stackedWidget->addWidget(m_loginPage);
    ui->stackedWidget->addWidget(m_registerPage);
    ui->stackedWidget->addWidget(m_forgetPWPage);

    // Set the default widget to m_loginPage
    ui->stackedWidget->setCurrentWidget(m_loginPage);

    // Connect buttons to switch between widgets
    connect(m_loginPage->findChild<QPushButton*>("btn_signUp"), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(m_registerPage);
    });
    connect(m_loginPage->findChild<QPushButton*>("btn_forgetPWD"), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(m_forgetPWPage);
    });
    connect(m_registerPage->findChild<QPushButton*>("pbtn_backToLogin"), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(m_loginPage);
    });
    connect(m_forgetPWPage->findChild<QPushButton*>("pbtn_backToLogin"), &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(m_loginPage);
    });
}

void login::onLoginSuccess()
{
    // 登录成功，关闭当前登录页面
    this->close();
}
