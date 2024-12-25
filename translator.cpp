#include "translator.h"
#include "ui_translator.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDateTime>
translator::translator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::translator)
{
    ui->setupUi(this);
    // 设置窗口标题
    setWindowTitle("简单翻译");


    ui->inputText->setPlaceholderText("在这里输入文本（输入中文或英文）...");


    ui->outputText->setReadOnly(true);
    ui->outputText->setPlaceholderText("翻译结果将显示在这里...");

    connect(ui->translateButton, &QPushButton::clicked, this, &translator::translateText);

    this->setStyleSheet(
        "#frame {"
        "    border-image: url(:/loginIMG/image/anyother.png);"
        "}"


    );
}

translator::~translator()
{
    delete ui;
}
void translator::translateText()
{
    // 获取用户输入的文本
    QString textToTranslate = ui->inputText->toPlainText().trimmed();
    if (textToTranslate.isEmpty()) {
        QMessageBox::warning(this, "输入为空", "请输入要翻译的文本。");
        return;
    }

    // 检测输入文本的语言类型
    QString targetLang;
    QString sourceLang;
    if (textToTranslate.at(0).isLower()) {
        targetLang = "zh"; // 翻译成中文
        sourceLang = "en"; // 英文
    } else {
        targetLang = "en"; // 翻译成英文
        sourceLang = "zh"; // 中文
    }


    // 发起网络请求进行翻译
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);//处理网络请求和响应
    QUrl url("http://api.fanyi.baidu.com/api/trans/vip/translate");//QUrl 对象用于设置请求的API地址
    QUrlQuery query;
    query.addQueryItem("q", textToTranslate);
    query.addQueryItem("from", sourceLang);
    query.addQueryItem("to", targetLang);
    query.addQueryItem("appid", "20240614002077265"); // 使用 QUrlQuery 构建请求参数，包括要翻译的文本 (q)、源语言 (from)、目标语言 (to) 和 API ID (appid)。

    // 计算salt和签名
    QString salt = QString::number(QDateTime::currentMSecsSinceEpoch() / 1000); // 使用秒级时间戳
    QString signStr = "20240614002077265" + textToTranslate + salt + "kdOkhnAqCC4YBriaC8TB"; // 替换为您的密钥
    QByteArray signBytes = QCryptographicHash::hash(signStr.toUtf8(), QCryptographicHash::Md5);
    QString sign = QString(signBytes.toHex()).toLower(); // 注意转换为小写

    query.addQueryItem("salt", salt);
    query.addQueryItem("sign", sign);//根据文本内容、时间戳和密钥计算签名 (sign)，用于验证请求的合法性。
    url.setQuery(query);

    qDebug() << "Request URL:" << url.toString(); // 输出请求的URL

    QNetworkRequest request(url); //将构建好的参数设置到请求的URL中，并使用 QNetworkRequest 创建请求对象。
    QNetworkReply *reply = manager->get(request);//通过 QNetworkAccessManager 发送GET请求，并获取响应的 reply 对象。

    connect(reply, &QNetworkReply::finished, this, [=]() {//finished 信号表示网络请求已完成，无论成功还是失败，都会触发这个信号
        if (reply->error() == QNetworkReply::NoError) { // 判断网络请求是否成功
            QByteArray responseData = reply->readAll();//获取服务器返回的所有数据，并存储在 responseData 中。
            qDebug() << "Response Data:" << responseData; // 输出响应内容以便调试

            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object(); //将 responseData 解析为 JSON 格式的文档 jsonDoc，然后获取其顶层对象 jsonObj
            if (jsonObj.contains("trans_result")) { //检查是否包含名为 "trans_result" 的字段
                QJsonArray transResultArray = jsonObj["trans_result"].toArray();//将 "trans_result" 转换为 JSON 数组 transResultArray。
                if (!transResultArray.isEmpty()) {//如果不为空，获取第一个翻译结果对象 translationObj，并从中提取翻译后的文本（目标语言） "dst"。
                    QJsonObject translationObj = transResultArray.first().toObject();
                    QString translatedText = translationObj["dst"].toString();
                    ui->outputText->setPlainText(translatedText);//将翻译结果设置到界面的文本框ui->outputText 中。
                } else {
                    ui->outputText->setPlainText("翻译失败：未找到翻译结果。");
                }
            } else {
                ui->outputText->setPlainText("翻译失败：未找到翻译结果。");
            }
        } else {
            ui->outputText->setPlainText("翻译失败：" + reply->errorString());
        }
        reply->deleteLater();
    });
}
