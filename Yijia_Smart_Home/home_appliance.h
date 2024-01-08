#ifndef HOME_APPLIANCE_H
#define HOME_APPLIANCE_H

#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class home_appliance;
}

class home_appliance : public QMainWindow
{
    Q_OBJECT

public:
    explicit home_appliance(QWidget *parent = nullptr);
    ~home_appliance();

private slots:
    void on_JD_Zhu_clicked();

    void on_LYJ_S_clicked();

    void on_LYJ_J_clicked();

private:
    Ui::home_appliance *ui;
    QNetworkAccessManager *manager;
private slots:
    void requestFinished(QNetworkReply *reply);

};

#endif // HOME_APPLIANCE_H
