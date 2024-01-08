#ifndef SHEZHI_H
#define SHEZHI_H

#include <QMainWindow>
#include "global.h" // 包含全局变量数组的头文件

namespace Ui {
class SheZhi;
}

class SheZhi : public QMainWindow
{
    Q_OBJECT

public:
    explicit SheZhi(QWidget *parent = nullptr);
    ~SheZhi();

private slots:

    void on_ZJM_BT_clicked();

private:
    Ui::SheZhi *ui;
};

#endif // SHEZHI_H
