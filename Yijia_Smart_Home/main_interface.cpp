#include "main_interface.h"
#include "ui_main_interface.h"
#include "home_appliance.h"
#include "illuminating.h"
#include "shezhi.h"

Main_interface::Main_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_interface)
{
    ui->setupUi(this);
}

Main_interface::~Main_interface()
{
    delete ui;
}

void Main_interface::on_ZhaoMing_clicked()
{
    home_appliance *ZM = new home_appliance;
    ZM ->show();
    this->close();
}

void Main_interface::on_JiaDian_clicked()
{
    Illuminating *JD = new Illuminating;
    JD->show();
    this->close();
}

void Main_interface::on_Shezhi_clicked()
{
    SheZhi *SZ = new SheZhi;
    SZ->show();
    this->close();
}
