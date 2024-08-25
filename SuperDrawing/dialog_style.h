#ifndef DIALOG_STYLE_H
#define DIALOG_STYLE_H

#include <QDialog>
#include<QCloseEvent> //бибилиотека с событием закрытия окна
#include<QMessageBox>
#include <QColorDialog>
#include<QMetaObject>
#include "mpen.h"

namespace Ui {
class Dialog_style;
}

class Dialog_style : public QDialog, public mpen
{
    Q_OBJECT

public:
    explicit Dialog_style(QWidget *parent = nullptr);
    ~Dialog_style();
    void setStyleVisible(bool fl);
    void setStyleBrushVisible(bool fl1);
    void setValue(mpen n_pen);

private slots:
    void closeEvent(QCloseEvent *event); //будем изменять обработчик закрытия формы

    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_colorLine_clicked();

    void on_pushButton_colorBrush_clicked();

    void on_comboBox_line_currentIndexChanged(int index);

    void on_comboBox_brush_currentIndexChanged(int index);

private:
    Ui::Dialog_style *ui;
    bool styleVisible = false;
    bool styleBrushVisible = false;
    QColor color_dialog_line;
    QColor color_dialog_brush;
};

#endif // DIALOG_STYLE_H
