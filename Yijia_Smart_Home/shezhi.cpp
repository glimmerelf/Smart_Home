// shezhi.cpp
#include "shezhi.h"
#include "ui_shezhi.h"
#include "main_interface.h"

SheZhi::SheZhi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SheZhi)
{
    ui->setupUi(this);
    ui->WoShi->setText(ipArray[0]);
    ui->YangTai->setText(ipArray[1]);
    ui->ChuFang->setText(ipArray[2]);
    ui->WC->setText(ipArray[3]);
}

SheZhi::~SheZhi()
{
    delete ui;
}

void SheZhi::on_ZJM_BT_clicked()
{
    Main_interface *ZJM = new Main_interface;
    ZJM->show();
    this->close();
    ipArray[0] = ui->WoShi->text();
    ipArray[1] = ui->YangTai->text();
    ipArray[2] = ui->ChuFang->text();
    ipArray[3] = ui->WC->text();
}
