#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "cell_login.h"
#include"cell_income.h"
#include"login.h"
#include"income.h"

#include <QtSql>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置数据库连接参数
    // 设置数据库连接参数
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("financeplaner");
    db.setPassword("cs18784855422..");
    db.setPort(3306);

    // 测试数据库连接是否成功
    if (!db.open()) {
        qDebug() << "无法连接到数据库：" << db.lastError().text();
        return 1;
    } else {
        qDebug() << "数据库连接成功！";
    }



        login m_login;


        m_login.show();

        return a.exec();

}
