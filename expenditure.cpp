#include "expenditure.h"
#include "ui_expenditure.h"
#include <QMessageBox>
#include <QDebug>
#include "cell_login.h"
#include "cell_expenditure.h"
#include<QtSql>
expenditure::expenditure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::expenditure)
{
    ui->setupUi(this);
    // 设置 dedit_time 默认为当前日期
    ui->dedit_time->setDate(QDate::currentDate());

    // 不再设置数据库连接参数，依赖于全局数据库连接 db

    // 初始化模型和表格视图
    setupModel();
    setupTableView();
    ui->tableView->setModel(model); // 将模型设置到表格视图中

    this->setStyleSheet(
        "#frame {"
        "    border-image: url(:/loginIMG/image/background-4.png);"
        "}"


    );
}

expenditure::~expenditure()
{
    delete ui;
}

void expenditure::setupModel()
{
    model = new QSqlQueryModel(this);
    updateTableView(); // 初始显示所有数据
}

void expenditure::setupTableView()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 让列自动填充宽度

       // 修改表头显示文本
       model->setHeaderData(0, Qt::Horizontal, "支出金额");
       model->setHeaderData(1, Qt::Horizontal, "支出种类");
       model->setHeaderData(2, Qt::Horizontal, "备注");
       model->setHeaderData(3, Qt::Horizontal, "支出时间");

       ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
       ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
       connect(ui->tableView, &QTableView::doubleClicked, this, &expenditure::onTableViewDoubleClicked);
}

void expenditure::updateTableView(const QString &type, const QString &date)
{
    QString queryStr = "SELECT money, typee, remarks, date "
                           "FROM expenditure "
                           "WHERE phone = '" + cell_login::getPhoneNumber() + "' ";

        // 根据类型和日期添加筛选条件
        if (type != "不限" && !type.isEmpty()) { // 仅当类型不是“不限”时才添加类型过滤器
            queryStr += "AND typee = '" + type + "' ";
        }
        if (!date.isEmpty()) {
            queryStr += "AND date = '" + date + "' ";
        }
        // 添加按日期排序
        queryStr += "ORDER BY date ASC";
        // 执行查询
        model->setQuery(queryStr);

        // 设置模型到表格视图中显示数据
        ui->tableView->setModel(model);

        // 如果查询结果为空，显示默认图片
       /* if (model->rowCount() == 0) {
            QPixmap pixmap(":/incomeIMG/image/noData.png");
            ui->label_image->setPixmap(pixmap.scaled(ui->label_image->size(), Qt::KeepAspectRatio));
        } else {
            ui->label_image->clear(); // 如果有结果，清空图片显示
        }*/
}

void expenditure::on_pbtn_search_clicked()
{
    QString type = ui->cbx_type->currentText(); // 获取选择的收入类型
    QString date = ui->dedit_time->date().toString("yyyy-MM-dd"); // 获取选择的日期并格式化为字符串

    updateTableView(type, date); // 更新表格视图
}

void expenditure::on_pbtn_replace_clicked()
{
    ui->cbx_type->setCurrentIndex(0); // 假设索引 0 是空/默认值
    ui->dedit_time->setDate(QDate::currentDate()); // 设置日期为当前日期

    updateTableView(); // 显示所有数据
}

void expenditure::on_pbtn_newAdd_clicked()
{
    // 创建加数据窗口
   cell_expenditure *m_cell_expenditure = new cell_expenditure;
    m_cell_expenditure->show();
}

void expenditure::onTableViewDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    int row = index.row();
    QString money = model->data(model->index(row, 0)).toString();
    QString type = model->data(model->index(row, 1)).toString();
    QString remarks = model->data(model->index(row, 2)).toString();
    QString date = model->data(model->index(row, 3)).toString();

    cell_expenditure *editWindow = new cell_expenditure;
    editWindow->setData(money, type, remarks, date);
    editWindow->show();
}

void expenditure::on_pbtn_delete_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

        if (selectedRows.isEmpty()) {
            QMessageBox::warning(this, "删除", "请先选择要删除的行！");
            return;
        }

        int row = selectedRows.first().row();
        QString money = model->data(model->index(row, 0)).toString();
        QString type = model->data(model->index(row, 1)).toString();
        QString remarks = model->data(model->index(row, 2)).toString();
        QString date = model->data(model->index(row, 3)).toString();
        QString phone = cell_login::getPhoneNumber();

        QSqlQuery query;
        query.prepare("DELETE FROM expenditure WHERE money = :money AND typee = :type AND remarks = :remarks AND date = :date AND phone = :phone");
        query.bindValue(":money", money);
        query.bindValue(":type", type);
        query.bindValue(":remarks", remarks);
        query.bindValue(":date", date);
        query.bindValue(":phone", phone);

        if (!query.exec()) {
            QMessageBox::critical(this, "数据库错误", "无法删除收入记录：" + query.lastError().text());
        } else {
            QMessageBox::information(this, "成功", "收入记录删除成功！");
            updateTableView(); // 删除成功后更新表格视图
        }
}

