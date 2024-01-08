#include "illuminating.h"
#include "ui_illuminating.h"
#include "main_interface.h"
#include "global.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

Illuminating::Illuminating(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Illuminating),
    manager(new QNetworkAccessManager(this)) // 初始化网络管理器
{
    ui->setupUi(this);
}

Illuminating::~Illuminating()
{
    delete ui;
}

void Illuminating::on_ZaoMin_Zhu_clicked()
{
    Main_interface *ZJM =new Main_interface;
    ZJM->show();
    this->close();
}

void Illuminating::on_WS_LED_ON_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[0]);//卧室节点IP

    // 打开LED灯
    request.setUrl(QUrl(url + "/LED/on"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED turned ON";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_WS_LED_OFF_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[0]);//卧室节点IP

    // 关闭LED灯
    request.setUrl(QUrl(url + "/LED/off"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED turned OFF";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_YT_ON_clicked()
{
    // 发送控制命令到Arduino，打开LED
       sendCommandToArduino("2"); // 2 是控制LED的命令
}

void Illuminating::on_YT_OFF_clicked()
{
    // 发送控制命令到Arduino，关闭LED
        sendCommandToArduino("2"); // 2 是控制LED的命令
}
void Illuminating::sendCommandToArduino(const QString& command)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // 替换为你的Arduino的IP地址或者主机名
    QString arduinoUrl = QString("http://%1/control?cmd=" + command).arg(ipArray[1]);//阳台节点IP

    QNetworkRequest request;
    request.setUrl(QUrl(arduinoUrl));

    connect(manager, &QNetworkAccessManager::finished, this, &Illuminating::onNetworkReply);

    manager->get(request);
}

void Illuminating::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Arduino command sent successfully.";
    } else {
        qDebug() << "Error sending Arduino command: " << reply->errorString();
    }

    reply->deleteLater();
}

void Illuminating::on_CF_ON_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[2]);//厨房节点IP

    // 打开LED灯
    request.setUrl(QUrl(url + "/LED/on"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED turned ON";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_CF_OFF_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[2]);//厨房节点IP

    // 关闭LED灯
    request.setUrl(QUrl(url + "/LED/off"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED turned OFF";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_WSJ_LED_ON_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[3]);//卫生间节点IP

    // 打开LED灯
    request.setUrl(QUrl(url + "/LED/on"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED turned ON";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_WSJ_LED_OFF_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[3]);;//卫生间节点IP

    // 关闭LED灯
    request.setUrl(QUrl(url + "/LED/off"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED turned OFF";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_brighter_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[0]);//卧室节点IP

    // 打开LED灯
    request.setUrl(QUrl(url + "/LED/brighter"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED brighter";
        }
        reply->deleteLater();
    });
}

void Illuminating::on_dimmer_clicked()
{
    QNetworkRequest request;
    // 设置ESP8266的IP地址和端口
    QString url = QString("http://%1:80").arg(ipArray[0]);//卧室节点IP

    // 关闭LED灯
    request.setUrl(QUrl(url + "/LED/dimmer"));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished, this, [reply] {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
        } else {
            qDebug() << "LED dimmer";
        }
        reply->deleteLater();
    });
}
