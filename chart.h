#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include<QtCharts>
namespace Ui {
class chart;
}

class chart : public QMainWindow
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr);
    ~chart();
private slots:
    void on_pbtn_drawIncomePieChart_2_clicked();
   void on_cbx_IncomeTime_2_currentIndexChanged(int index);
   void do_pieHovered(QPieSlice *slice, bool state);
   void on_spinHoleSize_valueChanged(double arg1);

   void on_spinPieSize_valueChanged(double arg1);
   //2
   void on_pbtn_drawExpendPieChart_2_clicked();
   void on_cbx_ExpendTime_3_currentIndexChanged(int index);

   void on_spinHoleSize_2_valueChanged(double arg1);

   void on_spinPieSize_2_valueChanged(double arg1);
private:
    Ui::chart *ui;
    //1
    void    iniPieChart();
   void drawPieChart();
   //2
   void    iniePieChart();
   void drawePieChart();

};

#endif // CHART_H
