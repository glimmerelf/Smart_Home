#ifndef ILLUMINATING_H
#define ILLUMINATING_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QWidget>
#include <QNetworkReply>

namespace Ui {
class Illuminating;
}

class Illuminating : public QMainWindow
{
    Q_OBJECT

public:
    explicit Illuminating(QWidget *parent = nullptr);
    ~Illuminating();

private slots:
    void on_ZaoMin_Zhu_clicked();

    void on_WS_LED_ON_clicked();

    void on_WS_LED_OFF_clicked();

    void on_YT_ON_clicked();

    void on_YT_OFF_clicked();
    void sendCommandToArduino(const QString& command);

    void onNetworkReply(QNetworkReply *reply);

    void on_CF_ON_clicked();

    void on_CF_OFF_clicked();

    void on_WSJ_LED_ON_clicked();

    void on_WSJ_LED_OFF_clicked();

    void on_brighter_clicked();

    void on_dimmer_clicked();

private:
    Ui::Illuminating *ui;
    QNetworkAccessManager *manager;
};

#endif // ILLUMINATING_H
