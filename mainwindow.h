#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "income.h" // 包含收入管理页面的头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:

    void    createSelectionMenu();   //创建下拉菜单
private slots:
    void on_pbtn_incomeControl_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_pbtn_expenditure_clicked();

    void on_btn_chart_clicked();

    void on_actExchangeRate_triggered();

    void on_actCalculate_triggered();

    void on_actQuit_triggered();

    void on_actUserChange_triggered();

    void on_actUserInfo_triggered();

    void on_actTransltor_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
