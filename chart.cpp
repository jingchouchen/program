#include "chart.h"
#include "ui_chart.h"
#include"cell_login.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
chart::chart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);
        iniPieChart();
        iniePieChart();

        // 初始化收入年份选择框
        QStringList years = {"2022", "2023", "2024"}; // 替换成从数据库获取的年份列表
        ui->cbx_incomeTypeOfTime_2->addItems(years);

        // 初始化月份选择框（收入）
        QStringList months = {"不限"}; // 添加“不限”选项
        for (int i = 1; i <= 12; ++i) {
            months << QString("%1月").arg(i);
        }
        ui->cbx_IncomeTime_2->addItems(months);

        // 初始化支出年份选择框
        QStringList eyears = {"2022", "2023", "2024"}; // 替换成从数据库获取的年份列表
        ui->cbx_expendTypeOfTime_3->addItems(eyears);

        // 初始化月份选择框（支出）
        QStringList emonths = {"不限"}; // 添加“不限”选项
        for (int i = 1; i <= 12; ++i) {
            emonths << QString("%1月").arg(i);
        }
        ui->cbx_ExpendTime_3->addItems(emonths);
}

chart::~chart()
{
    delete ui;
}

void chart::do_pieHovered(QPieSlice *slice, bool state)
{
    slice->setExploded(state);
}

void chart::iniPieChart()
{
    // 饼图初始化
    QChart *chart = new QChart();
    chart->setTitle("收入饼状图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    // chart->setAcceptHoverEvents(false); //chart不接受hover，由slice接受
    ui->IncomeGraphicsView_2->setChart(chart);
    ui->IncomeGraphicsView_2->setRenderHint(QPainter::Antialiasing);
}
void chart::drawPieChart()
{
    QChart *chart = ui->IncomeGraphicsView_2->chart();
        if (!chart) {
            chart = new QChart();
            ui->IncomeGraphicsView_2->setChart(chart);
        } else {
            chart->removeAllSeries();
        }

        QString year = ui->cbx_incomeTypeOfTime_2->currentText();
        QString monthText = ui->cbx_IncomeTime_2->currentText();
        int month = (monthText == "不限") ? 0 : ui->cbx_IncomeTime_2->currentIndex();

        QString phoneNumber = cell_login::getPhoneNumber();

        // 构建查询语句
        QString queryStr = "SELECT typee, SUM(money) AS total "
                           "FROM income "
                           "WHERE YEAR(date) = '" + year + "'";
        if (month > 0) {
            queryStr += " AND MONTH(date) = " + QString::number(month);
        }
        queryStr += " AND phone = '" + phoneNumber + "' "
                    "GROUP BY typee";

        QSqlQuery query;
        double totalIncome = 0.0;
        if (query.exec(queryStr)) {
            QPieSeries *series = new QPieSeries();
            bool hasData = false;
            while (query.next()) {
                hasData = true;
                QString type = query.value("typee").toString();
                double total = query.value("total").toDouble();
                totalIncome += total;  // 计算总收入
                series->append(type, total);
            }

            if (!hasData) {
                // 当月没有收入数据时显示提示信息
                QMessageBox::information(this, "No Data", QString("%1年%2无收入数据").arg(year).arg(monthText));
                return;
            }

            series->setLabelsVisible(true);
            QPieSlice *slice;
            for (int i = 0; i < series->slices().size(); ++i) {
                slice = series->slices().at(i);
                QString type = slice->label();
                double percentage = slice->value() / totalIncome * 100;
                slice->setLabel(QString("%1: %2 元 (%3%)")
                                .arg(type)
                                .arg(slice->value())
                                .arg(QString::number(percentage, 'f', 1)));
            }
            slice->setExploded(true);
            chart->setAcceptHoverEvents(true);

            chart->addSeries(series);
            chart->setTitle(QString(" %1 - %2的收入饼状图").arg(year).arg(monthText));
            connect(series, &QPieSeries::hovered, this, &chart::do_pieHovered);

            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);

            series->setHoleSize(ui->spinHoleSize->value());
        } else {
            qDebug() << "Error executing query: " << query.lastError().text();
        }
}
void chart::iniePieChart()
{
    // 饼图初始化
    QChart *chart = new QChart();
    chart->setTitle("支出饼状图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    // chart->setAcceptHoverEvents(false); //chart不接受hover，由slice接受
    ui->ExpendGraphicsView_3->setChart(chart);
    ui->ExpendGraphicsView_3->setRenderHint(QPainter::Antialiasing);
}
void chart::drawePieChart()//支出
{
    QChart *chart = ui->ExpendGraphicsView_3->chart();
        if (!chart) {
            chart = new QChart();
            ui->ExpendGraphicsView_3->setChart(chart);
        } else {
            chart->removeAllSeries();
        }

        QString year = ui->cbx_expendTypeOfTime_3->currentText();
        QString monthText = ui->cbx_ExpendTime_3->currentText();
        int month = (monthText == "不限") ? 0 : ui->cbx_ExpendTime_3->currentIndex();

        QString phoneNumber = cell_login::getPhoneNumber();

        // 构建查询语句
        QString queryStr = "SELECT typee, SUM(money) AS total "
                           "FROM expenditure "
                           "WHERE YEAR(date) = '" + year + "'";
        if (month > 0) {
            queryStr += " AND MONTH(date) = " + QString::number(month);
        }
        queryStr += " AND phone = '" + phoneNumber + "' "
                    "GROUP BY typee";

        QSqlQuery query;
        double totalExpenditure = 0.0;
        if (query.exec(queryStr)) {  //从数据库中获取收入或支出的类型和总金额。
            QPieSeries *series = new QPieSeries();
            bool hasData = false;
            while (query.next()) {
                hasData = true;  //标记为有数据。
                QString type = query.value("typee").toString();//获取支出类型
                double total = query.value("total").toDouble();
                totalExpenditure += total;  // 计算总支出
                series->append(type, total);//将类型和对应的总金额添加到饼状图系列中
            }
            if (!hasData) {
                // 当月没有支出数据时显示提示信息
                QMessageBox::information(this, "No Data", QString("%1年%2无支出数据").arg(year).arg(monthText));
                return;
            }
            series->setLabelsVisible(true);//设置饼状图中每个切片的标签可见性，使得用户可以看到每个切片的具体数值和百分比。
            QPieSlice *slice;//定义一个饼状图切片的指针，用于迭代访问每个切片
            for (int i = 0; i < series->slices().size(); ++i) {
                slice = series->slices().at(i);
                QString type = slice->label();
                double percentage = slice->value() / totalExpenditure * 100;
                slice->setLabel(QString("%1: %2 元 (%3%)")
                                .arg(type)
                                .arg(slice->value())
                                .arg(QString::number(percentage, 'f', 1)));//设置切片的标签内容，包括类型、金额和百分比信息。
            }
            slice->setExploded(true);//设置切片初始时为展开状态
            chart->setAcceptHoverEvents(true);//设置图表接受悬停事件

            chart->addSeries(series);
            chart->setTitle(QString(" %1 - %2的支出饼状图").arg(year).arg(monthText));
            connect(series, &QPieSeries::hovered, this, &chart::do_pieHovered);

            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);

            series->setHoleSize(ui->spinHoleSize_2->value());
        } else {
            qDebug() << "Error executing query: " << query.lastError().text();
        }
}
void chart::on_pbtn_drawIncomePieChart_2_clicked()
{
    drawPieChart();  // 绘制水平百分比柱状图
}

void chart::on_cbx_IncomeTime_2_currentIndexChanged(int index)
{
    Q_UNUSED(index); // To suppress unused parameter warning if not used
    // Call drawPieChart() or any other relevant logic based on the combobox index change
    // drawPieChart(); // Example: Refresh pie chart when combobox index changes
}

void chart::on_spinHoleSize_valueChanged(double arg1)
{
    // 设置HoleSize
    QPieSeries *series;
    series = static_cast<QPieSeries*>(ui->IncomeGraphicsView_2->chart()->series().at(0));
    series->setHoleSize(arg1);
}

void chart::on_spinPieSize_valueChanged(double arg1)
{
    // 设置pieSize
    QPieSeries *series;
    series = static_cast<QPieSeries*>(ui->IncomeGraphicsView_2->chart()->series().at(0));
    series->setPieSize(arg1);
}
void chart::on_cbx_ExpendTime_3_currentIndexChanged(int index)
{
    Q_UNUSED(index); // To suppress unused parameter warning if not used
    // Call drawPieChart() or any other relevant logic based on the combobox index change
    // drawPieChart(); // Example: Refresh pie chart when combobox index changes
}

void chart::on_spinHoleSize_2_valueChanged(double arg1)
{
    // 设置HoleSize
    QPieSeries *series;
    series = static_cast<QPieSeries*>(ui->ExpendGraphicsView_3->chart()->series().at(0));
    series->setHoleSize(arg1);
}

void chart::on_spinPieSize_2_valueChanged(double arg1)
{
    // 设置pieSize
    QPieSeries *series;
    series = static_cast<QPieSeries*>(ui->ExpendGraphicsView_3->chart()->series().at(0));
    series->setPieSize(arg1);
}
void chart::on_pbtn_drawExpendPieChart_2_clicked()
{
    drawePieChart();
}

