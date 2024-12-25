#include "calcutor.h"
#include "ui_calcutor.h"
#include <QDebug>
#include <cmath>

calcutor::calcutor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calcutor)
{
    ui->setupUi(this);
    // 初始化表达式为空

    expression = "";
    updateDisplay();
}

calcutor::~calcutor()
{
    delete ui;
}

void calcutor::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0:
        on_pushButton_0_clicked();
        break;
    case Qt::Key_1:
        on_pushButton_1_clicked();
        break;
    case Qt::Key_2:
        on_pushButton_2_clicked();
        break;
    case Qt::Key_3:
        on_pushButton_3_clicked();
        break;
    case Qt::Key_4:
        on_pushButton_4_clicked();
        break;
    case Qt::Key_5:
        on_pushButton_5_clicked();
        break;
    case Qt::Key_6:
        on_pushButton_6_clicked();
        break;
    case Qt::Key_7:
        on_pushButton_7_clicked();
        break;
    case Qt::Key_8:
        on_pushButton_8_clicked();
        break;
    case Qt::Key_9:
        on_pushButton_9_clicked();
        break;
    case Qt::Key_Period:
        on_pushButton_decPoint_clicked();
        break;
    case Qt::Key_Plus:
        on_pushButton_plus_clicked();
        break;
    case Qt::Key_Minus:
        on_pushButton_minus_clicked();
        break;
    case Qt::Key_Asterisk:
        on_pushButton_by_clicked();
        break;
    case Qt::Key_Slash:
        on_pushButton_divide_clicked();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        on_pushButton_equal_clicked();
        break;
    case Qt::Key_Delete:
        on_pushButton_delete_clicked();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void calcutor::on_pushButton_0_clicked()
{
    expression += "0";
    updateDisplay();
}

void calcutor::on_pushButton_1_clicked()
{
    expression += "1";
    updateDisplay();
}

void calcutor::on_pushButton_2_clicked()
{
    expression += "2";
    updateDisplay();
}

void calcutor::on_pushButton_3_clicked()
{
    expression += "3";
    updateDisplay();
}

void calcutor::on_pushButton_4_clicked()
{
    expression += "4";
    updateDisplay();
}

void calcutor::on_pushButton_5_clicked()
{
    expression += "5";
    updateDisplay();
}

void calcutor::on_pushButton_6_clicked()
{
    expression += "6";
    updateDisplay();
}

void calcutor::on_pushButton_7_clicked()
{
    expression += "7";
    updateDisplay();
}

void calcutor::on_pushButton_8_clicked()
{
    expression += "8";
    updateDisplay();
}

void calcutor::on_pushButton_9_clicked()
{
    expression += "9";
    updateDisplay();
}

void calcutor::on_pushButton_decPoint_clicked()
{
    expression += ".";
    updateDisplay();
}

void calcutor::on_pushButton_plus_clicked()
{
    expression += "+";
    updateDisplay();
}

void calcutor::on_pushButton_minus_clicked()
{
    expression += "-";
    updateDisplay();
}

void calcutor::on_pushButton_by_clicked()
{
    expression += "×";
    updateDisplay();
}

void calcutor::on_pushButton_divide_clicked()
{
    expression += "÷";
    updateDisplay();
}

void calcutor::on_pushButton_equal_clicked()
{
    // 检查最后一个字符是否为运算符
    if (expression.isEmpty() || expression.endsWith("+") || expression.endsWith("-") ||
            expression.endsWith("×") || expression.endsWith("÷")) {
        showError();
        return;
    }

    // 将 × 和 ÷ 替换为 * 和 /
    QString evalExpression = expression;
    evalExpression.replace("×", "*");
    evalExpression.replace("÷", "/");

    // 尝试计算表达式
    try {
        QString result = QString::number(eval(evalExpression.toStdString().c_str()), 'g', 15); // 调用 eval 函数计算表达式
        expression = result;
        updateDisplay();
    } catch (...) {
        showError();
    }
}

void calcutor::on_pushButton_clear_clicked()
{
    expression = "";
    updateDisplay();
}

void calcutor::on_pushButton_delete_clicked()
{
    if (!expression.isEmpty()) {
        expression.chop(1); // 删除最后一个字符
        updateDisplay();
    }
}

void calcutor::updateDisplay()
{
    ui->plainTextEdit->setPlainText(expression);
}

void calcutor::showError()
{
    ui->plainTextEdit->setPlainText("非法操作");
}

// 实现一个简单的计算器 eval 函数
double calcutor::eval(const char *str)
{
    // 这是一个简单的示例实现，可以根据需求进一步扩展和完善
    char *end;
    double result = strtod(str, &end);

    while (*end) {
        char op = *end;
        double next = strtod(end + 1, &end);
        switch (op) {
        case '+': result += next; break;
        case '-': result -= next; break;
        case '*': result *= next; break;
        case '/': result /= next; break;
        default:
            throw std::invalid_argument("非法操作");
        }
    }

    return result;
}
