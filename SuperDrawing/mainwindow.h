#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QColorDialog>
#include <QTableWidgetItem>
#include <QCryptographicHash>
#include <QDebug>
#include <QDataStream>

#include "my_widget.h"

#include "dialog_style.h"
#include "dialog_points.h"

#include "mpen.h"
#include "pixel.h"
#include "line.h"
#include "rect.h"
#include "ellips.h"
#include "circle.h"
#include "m_arc.h"
#include "chord.h"
#include "m_pie.h"
#include "polyline.h"
#include "polygon.h"
#include "triangle.h"
#include <math.h>

#define KOL_COL 8 //максимально количество столбцов

namespace Ui {
class MainWindow;
}



struct T_OBJ_DATA
{
    mpen my_pen;
    int kol;
    int * mas;   //будем писать всё подряд по "тайному алгоритму"
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    T_OBJ_DATA * obj_data;

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_Save_clicked();

    void on_pushButton_draw_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_Load_clicked();

    void closeEvent(QCloseEvent *event); //обработчик закрытия формы

    void on_pushButton_Save_as_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_SaveWidget_clicked();

private:
    Ui::MainWindow *ui;
    QString file1 = ""; //глобальная переменная для пути файла
    QString fileName = ""; //путь файла
    QString way = "Новый файл"; //глобальная переменна отвечающая за название файла
    QString file2 = "";
    bool correct_value = true;
    QByteArray fileHash;

protected slots:
    void Combo_click(int arg1);
    void style_click(void);
    void points_click(void);
};

#endif // MAINWINDOW_H
