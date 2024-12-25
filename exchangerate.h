#ifndef EXCHANGERATE_H
#define EXCHANGERATE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

namespace Ui {
class exchangeRate;
}

class exchangeRate : public QWidget
{
    Q_OBJECT

public:
    explicit exchangeRate(QWidget *parent = nullptr);
    ~exchangeRate();

private slots:
    void onAmount1Changed();
    void onAmount2Changed();
    void onCurrencyChanged();
    void replyFinished(QNetworkReply *reply);


private:
    Ui::exchangeRate *ui;
    QNetworkAccessManager *networkManager;
    QMap<QString, double> rates;
    bool updating;

    void fetchRates(const QString &baseCurrency);
    void updateConversion();


};

#endif // EXCHANGERATE_H
