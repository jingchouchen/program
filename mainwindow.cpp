#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "income.h" // 包含收入管理页面的头文件
#include"expenditure.h"//包含支出管理页面的头文件
#include"chart.h"//包含图表页面的头文件
#include"exchangerate.h"//汇率转换
#include"calcutor.h"//计算器
#include"login.h"//登录界面
#include"cell_userinformation.h"//用户信息
#include"translator.h"//翻译
#include"chart.h"//饼状图
void MainWindow::createSelectionMenu()
{
//创建下拉菜单(工具箱)
    QMenu* menuSelection=new QMenu(this);       //创建下拉菜单
    menuSelection->addAction(ui->actCalculate);    //计算器
    menuSelection->addAction(ui->actExchangeRate);   //汇率转换
     menuSelection->addAction(ui->actTransltor);   //翻译
   // menuSelection->addAction(ui->actSelInvs);   //反选


//工具栏上的下拉式菜单按钮
    QToolButton  *aBtn=new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);      //立刻下拉菜单，按钮关联的Action不会被执行
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actSelPopMenu);          //关联Action
    aBtn->setMenu(menuSelection);       //设置下拉菜单
    ui->toolBar->addWidget(aBtn);   //工具栏上添加按钮
    //创建下拉菜单(用户信息)
        QMenu* menuUserSelection=new QMenu(this);       //创建下拉菜单
        menuUserSelection->addAction(ui->actUserInfo);  //用户信息
       menuUserSelection->addAction(ui->actUserChange);//切换用户
       menuUserSelection->addAction(ui->actQuit); //退出程序
       // menuSelection->addAction(ui->actSelInvs);   //反选


    //工具栏上的下拉式菜单按钮
        QToolButton  *userBtn=new QToolButton(this);
        userBtn->setPopupMode(QToolButton::InstantPopup);      //立刻下拉菜单，按钮关联的Action不会被执行
        userBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        userBtn->setDefaultAction(ui->actUser);          //关联Action
        userBtn->setMenu(menuUserSelection);       //设置下拉菜单
        ui->toolBar->addWidget(userBtn);   //工具栏上添加按钮
//工具栏添加分隔条和“退出”按钮
    //ui->toolBar->addSeparator();
  ui->toolBar->setStyleSheet("background-color: rgb(200, 200, 200);");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//ui->tabWidget->setVisible(false);//先设置tabWidget为不可见
ui->tabWidget->clear();//清空tabWidget
createSelectionMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbtn_incomeControl_clicked()
{
    // 创建收入管理页面的实例
        income *incomePage = new income(this); // 假设 Income 是 income.h 中的窗口类
        incomePage->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除

        // 添加到 tabWidget 中显示
        int cur = ui->tabWidget->addTab(incomePage, "收入管理");
        ui->tabWidget->setCurrentIndex(cur);
        ui->tabWidget->setVisible(true);

        // 设置 incomePage 的大小为 tabWidget 的大小
        incomePage->resize(ui->tabWidget->size());
}



void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget(index)->close();
}


void MainWindow::on_pbtn_expenditure_clicked()
{
    // 创建支出管理页面的实例
        expenditure *expenditurePage = new expenditure(this); // 假设 Income 是 income.h 中的窗口类
        expenditurePage->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除

        // 添加到 tabWidget 中显示
        int cur = ui->tabWidget->addTab(expenditurePage, "支出管理");
        ui->tabWidget->setCurrentIndex(cur);
        ui->tabWidget->setVisible(true);

        // 设置 incomePage 的大小为 tabWidget 的大小
        expenditurePage->resize(ui->tabWidget->size());
}


void MainWindow::on_btn_chart_clicked()
{
    // 创建图表页面的实例
        chart *chartPage = new chart(this); // 假设 Income 是 income.h 中的窗口类
        chartPage->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除

        // 添加到 tabWidget 中显示
        int cur = ui->tabWidget->addTab(chartPage, "图表");
        ui->tabWidget->setCurrentIndex(cur);
        ui->tabWidget->setVisible(true);

        // 设置 incomePage 的大小为 tabWidget 的大小
        chartPage->resize(ui->tabWidget->size());
}


void MainWindow::on_actExchangeRate_triggered()
{
    exchangeRate *m_exchangeRate = new exchangeRate;
    m_exchangeRate->show();
}


void MainWindow::on_actCalculate_triggered()
{
    calcutor *m_calcutor = new calcutor;
    m_calcutor->show();
}


void MainWindow::on_actQuit_triggered()
{
    this->close();
}


void MainWindow::on_actUserChange_triggered()
{  login *m_login = new login();
    m_login->show();
    this->close();

}


void MainWindow::on_actUserInfo_triggered()
{
    cell_userInformation *m_cell_userInformation = new cell_userInformation;
    m_cell_userInformation->show();
}


void MainWindow::on_actTransltor_triggered()
{
    translator *m_translator = new translator;
    m_translator->show();
}

