#include "exchangeRate.h"
#include "ui_exchangeRate.h"

#include    <QSettings>

exchangeRate::exchangeRate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::exchangeRate)
    , networkManager(new QNetworkAccessManager(this))
    , updating(false)
{
    ui->setupUi(this);

    // 初始化默认值
ui->comboBox_1->addItem("人民币", "CNY");
ui->comboBox_1->addItem("美元", "USD");
ui->comboBox_1->addItem("欧元", "EUR");
ui->comboBox_1->addItem("日元", "JPY");
ui->comboBox_1->addItem("英镑", "GBP");
ui->comboBox_1->addItem("澳大利亚元", "AUD");
ui->comboBox_1->addItem("瑞士法郎", "CHF");
ui->comboBox_1->addItem("瑞典克朗", "SEK");
ui->comboBox_1->addItem("加拿大元", "CAD");
ui->comboBox_1->addItem("新西兰元", "NZD");
ui->comboBox_1->addItem("韩元", "KRW");
ui->comboBox_1->addItem("新加坡元", "SGD");
ui->comboBox_1->addItem("印度卢比", "INR");
ui->comboBox_1->addItem("卢布", "RUB");
ui->comboBox_1->addItem("巴西雷亚尔", "BRL");
ui->comboBox_1->addItem("南非兰特", "ZAR");
ui->comboBox_1->addItem("土耳其里拉", "TRY");
ui->comboBox_1->addItem("墨西哥比索", "MXN");
ui->comboBox_1->addItem("挪威克朗", "NOK");
ui->comboBox_1->addItem("丹麦克朗", "DKK");
ui->comboBox_1->addItem("波兰兹罗提", "PLN");
ui->comboBox_1->addItem("匈牙利福林", "HUF");
ui->comboBox_1->addItem("捷克克朗", "CZK");
ui->comboBox_1->addItem("马来西亚林吉特", "MYR");
ui->comboBox_1->addItem("印尼盾", "IDR");
ui->comboBox_1->addItem("泰铢", "THB");
ui->comboBox_1->addItem("菲律宾比索", "PHP");
ui->comboBox_1->addItem("以色列新谢克尔", "ILS");
ui->comboBox_1->addItem("阿根廷比索", "ARS");
ui->comboBox_1->addItem("沙特里亚尔", "SAR");

ui->comboBox_2->addItem("人民币", "CNY");
ui->comboBox_2->addItem("美元", "USD");
ui->comboBox_2->addItem("欧元", "EUR");
ui->comboBox_2->addItem("日元", "JPY");
ui->comboBox_2->addItem("英镑", "GBP");
ui->comboBox_2->addItem("澳大利亚元", "AUD");
ui->comboBox_2->addItem("瑞士法郎", "CHF");
ui->comboBox_2->addItem("瑞典克朗", "SEK");
ui->comboBox_2->addItem("加拿大元", "CAD");
ui->comboBox_2->addItem("新西兰元", "NZD");
ui->comboBox_2->addItem("韩元", "KRW");
ui->comboBox_2->addItem("新加坡元", "SGD");
ui->comboBox_2->addItem("印度卢比", "INR");
ui->comboBox_2->addItem("卢布", "RUB");
ui->comboBox_2->addItem("巴西雷亚尔", "BRL");
ui->comboBox_2->addItem("南非兰特", "ZAR");
ui->comboBox_2->addItem("土耳其里拉", "TRY");
ui->comboBox_2->addItem("墨西哥比索", "MXN");
ui->comboBox_2->addItem("挪威克朗", "NOK");
ui->comboBox_2->addItem("丹麦克朗", "DKK");
ui->comboBox_2->addItem("波兰兹罗提", "PLN");
ui->comboBox_2->addItem("匈牙利福林", "HUF");
ui->comboBox_2->addItem("捷克克朗", "CZK");
ui->comboBox_2->addItem("马来西亚林吉特", "MYR");
ui->comboBox_2->addItem("印尼盾", "IDR");
ui->comboBox_2->addItem("泰铢", "THB");
ui->comboBox_2->addItem("菲律宾比索", "PHP");
ui->comboBox_2->addItem("以色列新谢克尔", "ILS");
ui->comboBox_2->addItem("阿根廷比索", "ARS");
ui->comboBox_2->addItem("沙特里亚尔", "SAR");


    ui->comboBox_1->setCurrentIndex(0); // 默认人民币
    ui->comboBox_2->setCurrentIndex(1); // 默认美元

    // 连接信号和槽
    connect(ui->lineEdit_1, &QLineEdit::textChanged, this, &exchangeRate::onAmount1Changed);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &exchangeRate::onAmount2Changed);
    connect(ui->comboBox_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &exchangeRate::onCurrencyChanged);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &exchangeRate::onCurrencyChanged);

    fetchRates("CNY");

    this->setStyleSheet(
        "#frame_4, #frame_3{"
        "    border-image: url(:/loginIMG/image/background-4.png);"
        "}"


    );
}


exchangeRate::~exchangeRate()
{
    delete ui;
}

void exchangeRate::onAmount1Changed()
{
    if (updating) return;

    updating = true;
    updateConversion();
    updating = false;
}

void exchangeRate::onAmount2Changed()
{
    if (updating) return;

    updating = true;
    updateConversion();
    updating = false;
}

void exchangeRate::onCurrencyChanged()
{
    fetchRates(ui->comboBox_1->currentData().toString());
}

void exchangeRate::fetchRates(const QString &baseCurrency)
{
    QString url = QString("https://v6.exchangerate-api.com/v6/d64d1179bbf530cf60f28ab1/latest/%1").arg(baseCurrency);
    QNetworkRequest request{QUrl(url)}; //通过 QString::arg() 方法将 baseCurrency 插入到URL中
//构建了一个URL，用来向外部API请求汇率数据。这个URL包含了固定的API基地址以及一个动态的基准货币参数
    //创建了一个 QNetworkRequest 对象，用于封装URL请求。
    connect(networkManager, &QNetworkAccessManager::finished, this, &exchangeRate::replyFinished);
    //当网络请求完成时，会自动调用 replyFinished 函数处理返回的数据。
    networkManager->get(request);
    // 负责处理网络访问,发送GET请求，获取指定URL的数据。
}


void exchangeRate::replyFinished(QNetworkReply *reply)
{     //检查网络请求是否出错
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }
//读取返回的数据，保存在 QByteArray 对象 data 中
    QByteArray data = reply->readAll();
    //将 data 解析为 QJsonDocument 对象，以便后续处理JSON格式的数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//检查是否成功创建了 QJsonDocument 对象
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to create JSON doc.";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    if (jsonObj.contains("conversion_rates")) {//检查JSON对象中是否包含 "conversion_rates" 键，该键对应着汇率数据
        QJsonObject ratesObj = jsonObj["conversion_rates"].toObject();
        rates.clear();
        for (const QString &key : ratesObj.keys()) {
            rates[key] = ratesObj[key].toDouble();
        }// 将每个货币对应的汇率值转换为 double 类型，并存储在 rates 字典中，其中 key 是货币代号，rates[key] 是对应的汇率值
        updateConversion();
    } else {
        qDebug() << "Error: Conversion rates not found in response.";
    }

    reply->deleteLater();
}

void exchangeRate::updateConversion()
{
    QString fromCurrency = ui->comboBox_1->currentData().toString();
    QString toCurrency = ui->comboBox_2->currentData().toString();

    if (ui->lineEdit_1->hasFocus()) {
        double amount1 = ui->lineEdit_1->text().toDouble();
        double rate = rates[toCurrency] / rates[fromCurrency];
        double amount2 = amount1 * rate;
        ui->lineEdit_2->setText(QString::number(amount2, 'f', 2));
    } else if (ui->lineEdit_2->hasFocus()) {
        double amount2 = ui->lineEdit_2->text().toDouble();
        double rate = rates[fromCurrency] / rates[toCurrency];
        double amount1 = amount2 * rate;
        ui->lineEdit_1->setText(QString::number(amount1, 'f', 2));
    }
}
