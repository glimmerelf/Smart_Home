#include "home_appliance.h"
#include "ui_home_appliance.h"
#include "main_interface.h"
#include <QNetworkReply>
#include "global.h"


home_appliance::home_appliance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::home_appliance)
{
    ui->setupUi(this);
}

home_appliance::~home_appliance()
{
    delete ui;
}

void home_appliance::on_JD_Zhu_clicked()
{
    Main_interface *ZJM = new Main_interface;
    ZJM->show();
    this->close();
}

void home_appliance::on_LYJ_S_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

        QString url = QString("http://%1/control?cmd=0").arg(ipArray[1]);
         // //阳台节点IP
        QNetworkRequest request(url);
        manager->get(request);
    }

void home_appliance::requestFinished(QNetworkReply *reply)
{
    // 处理HTTP请求的响应
    if (reply->url().toString() == QString("http://%1/control?cmd=0").arg(ipArray[1])) { // 阳台节点IP
        // 处理LYJ_S按钮的请求
        if (reply->error() == QNetworkReply::NoError) {
            // 请求成功
            qDebug() << "Rotate clockwise";
        } else {
            // 请求失败
            qDebug() << "Failed to rotate clockwise";
        }
    } else if (reply->url().toString() == QString("http://%1/control?cmd=1").arg(ipArray[1])) {//阳台节点IP
        // 处理LYJ_J按钮的请求
        if (reply->error() == QNetworkReply::NoError) {
            // 请求成功
            qDebug() << "Rotate counterclockwise";
        } else {
            // 请求失败
            qDebug() << "Failed to rotate counterclockwise";
        }
    }

    reply->deleteLater();
}


void home_appliance::on_LYJ_J_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

       QString url = QString("http://%1/control?cmd=1").arg(ipArray[1]);//阳台节点IP
        QNetworkRequest request(url);
        manager->get(request);
    }



