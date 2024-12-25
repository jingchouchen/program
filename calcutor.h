#ifndef CALCUTOR_H
#define CALCUTOR_H

#include <QMainWindow>
#include <QKeyEvent>
namespace Ui {
class calcutor;
}

class calcutor : public QMainWindow
{
    Q_OBJECT

public:
    explicit calcutor(QWidget *parent = nullptr);
    ~calcutor();
protected:
    void keyPressEvent(QKeyEvent *event) override; // 捕获键盘按键事件

private slots:
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_decPoint_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_by_clicked();
    void on_pushButton_divide_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_delete_clicked();
private:
    Ui::calcutor *ui;
    QString expression; // 保存用户输入的表达式

    void updateDisplay(); // 更新显示
    void showError(); // 显示错误信息
    double eval(const char *str); // 计算表达式的函数声明
};

#endif // CALCUTOR_H
