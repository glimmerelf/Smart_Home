#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H

#include <QMainWindow>


namespace Ui {
class Main_interface;
}

class Main_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_interface(QWidget *parent = nullptr);
    ~Main_interface();

private slots:
    void on_ZhaoMing_clicked();

    void on_JiaDian_clicked();

    void on_Shezhi_clicked();

private:
    Ui::Main_interface *ui;
};

#endif // MAIN_INTERFACE_H
