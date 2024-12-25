#ifndef EXPENDITURE_H
#define EXPENDITURE_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QModelIndex>

namespace Ui {
class expenditure;
}

class expenditure : public QWidget
{
    Q_OBJECT
private slots:
    void on_pbtn_search_clicked();
    void on_pbtn_replace_clicked();
    void on_pbtn_newAdd_clicked();
    void onTableViewDoubleClicked(const QModelIndex &index);

    void on_pbtn_delete_clicked();
public:
    explicit expenditure(QWidget *parent = nullptr);
    ~expenditure();

private:
    Ui::expenditure *ui;
    QSqlQueryModel *model;

    void setupModel();
    void setupTableView();
    void updateTableView(const QString &type = QString(), const QString &date = QString());
};

#endif // EXPENDITURE_H
