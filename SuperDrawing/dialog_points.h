#ifndef DIALOG_POINTS_H
#define DIALOG_POINTS_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class Dialog_points;
}

class Dialog_points : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_points(QWidget *parent = nullptr);
    ~Dialog_points();
    bool setValue(int kol, int * mas); //будем передавать координаты подряд можно заменить двумерным
    bool getValue(int &kol, int * &mas);


private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void closeEvent(QCloseEvent *event); //обработчик закрытия формы

private:
    Ui::Dialog_points *ui;
    bool is_ok;
    bool no_auto_change; //изменения в таблице
    bool ok;
};

#endif // DIALOG_POINTS_H
