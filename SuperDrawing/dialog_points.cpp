#include "dialog_points.h"
#include "ui_dialog_points.h"

Dialog_points::Dialog_points(QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Dialog_points)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Точечки");
    is_ok=false;
}

Dialog_points::~Dialog_points() //деструктор
{
    delete ui;
}

void Dialog_points::on_spinBox_valueChanged(int arg1) //создание строк
{
    ui->tableWidget->setRowCount(arg1);
}

void Dialog_points::on_pushButton_Ok_clicked() //обработки кнопки Ok
{
    ok = true;
    //проверка значений таблицы
    int *mas = nullptr;

    int row = ui -> tableWidget -> rowCount();
    mas = new int[row];
    bool is_correct;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < 2; ++j) {
            if(ui -> tableWidget->item(i,j) != nullptr)
            {
                ui -> tableWidget ->item(i,j)->setBackground(Qt::white);
                mas[i] = ui->tableWidget->item(i,j)->text().toInt(&is_correct);
                if(!is_correct or mas[i] < -32000 or mas[i] > 32000)
                {
                    ok = false;
                }
            }
            else
            {
                for(int i = 0; i < row; ++i){
                    for(int j = 0; j < 2; j++)
                    {
                        if(ui -> tableWidget->item(i,j) == nullptr)
                        {
                            QTableWidgetItem * new_item;//создаем указатель
                            new_item = new QTableWidgetItem;//выделяем память
                            ui -> tableWidget -> setItem(i, j, new_item);//заносим указатель в таблицу
                            ui -> tableWidget ->item(i,j)->setBackground(Qt::red);//красим в красный
                        }
                    }
                 }
                 ok = false;
             }
         }
    }

    delete [] mas;
    mas = nullptr;
    no_auto_change = true;
    if(ok == true)
    {
        is_ok = true;
        //close();
        done(0);
    }
    else{
        QMessageBox::information(this,"Ошибка!","Некорректные значения в таблице!");
        return;
    }
}

void Dialog_points::closeEvent(QCloseEvent *event) //обработчик закрытия формы
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Внимание!", "Сохранить значения?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        on_pushButton_Ok_clicked();
        if(ok == false){
            event -> ignore();
        }
        else{
            event -> accept();
        }
    }
    else
    {
        is_ok = false;
        event -> accept();
    }
}

void Dialog_points::on_pushButton_Cancel_clicked() //обработка кнопки Cancel
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Внимание!", "Вы уверены, что хотите выйти? Все изменения НЕ будут сохранены.", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        is_ok = false;
        //close();
        done(0);
    }
    else
    {
        return;
    }
}


bool Dialog_points::setValue(int kol, int *mas) //передача значений
{
    is_ok=false;
    if ((kol<3)||(kol>ui->spinBox->maximum()))
    {
        return (false);
    }
    ui->spinBox->setValue(kol);
    if (mas==nullptr)
    {
        return (false);
    }
    else
    {
        int i = 0;
        for (int j = 0;j < kol;j++)
        {
            if (ui->tableWidget->item(j,0)==nullptr)
            {
                QTableWidgetItem * ti = new QTableWidgetItem;
                ui->tableWidget->setItem(j,0,ti);
            }
            ui->tableWidget->item(j,0)->setText(QString::number(mas[i++]));

            if (ui->tableWidget->item(j,1)==nullptr)
            {
                QTableWidgetItem * ti = new QTableWidgetItem;
                ui->tableWidget->setItem(j,1,ti);
            }
            ui->tableWidget->item(j,1)->setText(QString::number(mas[i++]));
        }
    }
    return (true);
}

bool Dialog_points::getValue(int &kol, int *&mas) //принятие значений
{
    if (!is_ok)
    {
        kol=0;
        mas=nullptr;
        return (false);
    }

    kol = ui->spinBox->value();

    mas = new int[kol+kol];
    int i=0;
    for (int j=0;j<kol;j++)
    {
        if (ui->tableWidget->item(j,0)==nullptr)
            mas[i++]=0;
        else
            mas[i++]=ui->tableWidget->item(j,0)->text().toInt();

        if (ui->tableWidget->item(j,1)==nullptr)
            mas[i++]=0;
        else
            mas[i++]=ui->tableWidget->item(j,1)->text().toInt();
    }
    return (true);
}

void Dialog_points::on_tableWidget_cellChanged(int row, int column) //проверка на ручное изменение в таблице
{
    bool is_correct;
    if (no_auto_change)
    {
        ui -> tableWidget -> item(row, column) -> text().toInt(&is_correct);
        if (is_correct)
        {
            ui -> tableWidget -> item(row, column) -> setBackground(Qt::white);
        }
        else
        {
            ui -> tableWidget -> item(row, column) -> setBackground(Qt::red);
        }
    }
}

