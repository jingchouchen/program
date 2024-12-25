#ifndef INCOME_H
#define INCOME_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QModelIndex>

namespace Ui {
class income;
}

class income : public QWidget
{
    Q_OBJECT

public:
    explicit income(QWidget *parent = nullptr);
    ~income();

private slots:
    void on_pbtn_search_clicked();
    void on_pbtn_replace_clicked();
    void on_pbtn_newAdd_clicked();
    void onTableViewDoubleClicked(const QModelIndex &index);

    void on_pbtn_delete_clicked();

private:
    Ui::income *ui;
    QSqlQueryModel *model;

    void setupModel();
    void setupTableView();
    void updateTableView(const QString &type = QString(), const QString &date = QString());
};

#endif // INCOME_H
