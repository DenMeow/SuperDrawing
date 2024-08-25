#include "dialog_style.h"
#include "ui_dialog_style.h"

Dialog_style::Dialog_style(QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Dialog_style)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Настройки");
}

Dialog_style::~Dialog_style() //деструктор
{
    delete ui;
}

void Dialog_style::setValue(mpen n_pen) //передача значений в mainwindow
{
    pen_style = n_pen.GetStyle();
    brush_style = n_pen.GetStyleBrush();

    if(brush_style == 0){
        ui -> pushButton_colorBrush -> hide();
        ui -> label_brush -> hide();
    }
    if(pen_style == 0){
        ui -> pushButton_colorLine -> hide();
        ui ->label_width -> hide();
        ui -> spinBox_Width -> hide();
        ui -> label_line -> hide();
    }

    pen_width = n_pen.GetWidth();

    //ЦВЕТ ЛИНИИ
    n_pen.GetRGBA(red_l,green_l,blue_l,alpha_l);
    color_dialog_line.setRgb(red_l,green_l,blue_l,alpha_l);
    ui->pushButton_colorLine->setStyleSheet(QString("background-color: %1").arg(color_dialog_line.name()));//выводим цвет

    //ЗАЛИВКА
    n_pen.GetRGBA_brush(red_b,green_b,blue_b,alpha_b);
    color_dialog_brush.setRgb(red_b,green_b,blue_b,alpha_b);
    ui->pushButton_colorBrush->setStyleSheet(QString("background-color: %1").arg(color_dialog_brush.name())); //выводим цвет

    //если  точка
    ui -> comboBox_line->setVisible(styleVisible);
    ui -> label_style->setVisible(styleVisible);
    ui -> label_line -> setVisible(styleVisible);

    //если до точки выбрали нет стиля
    if(pen_style == 0 and styleVisible == false){
        ui -> pushButton_colorLine -> show();
        ui -> label_width -> show();
        ui -> spinBox_Width -> show();
    }

    //если фигура не имеет заливки
    if(styleBrushVisible == false){
        ui -> pushButton_colorBrush->hide();
        ui->comboBox_brush->hide();
        ui->label_style_2->hide();
    }
    else{
        if(brush_style == 0){
            ui -> pushButton_colorBrush->hide();
        }
        else{
            ui -> pushButton_colorBrush->show();
        }
        ui->comboBox_brush->show();
        ui->label_style_2->show();
    }

    ui->comboBox_line->setCurrentIndex(pen_style); //стиль линии
    ui->comboBox_brush->setCurrentIndex(brush_style); //стиль заливки
    ui->spinBox_Width->setValue(pen_width); //толщина
}


void Dialog_style::setStyleVisible(bool fl) //проверка на то что рисуем не точку
{
    styleVisible=fl;
}
void Dialog_style::setStyleBrushVisible(bool fl1) //проверка на то что рисуем фигуру с заливкой
{
    styleBrushVisible=fl1;
}

void Dialog_style::on_pushButton_Ok_clicked() //обработчик нажатия ОК
{
    //цвет линии
    red_l = color_dialog_line.red();
    green_l = color_dialog_line.green();
    blue_l = color_dialog_line.blue();
    alpha_l = color_dialog_line.alpha();
    //цвет заливки
    red_b = color_dialog_brush.red();
    green_b = color_dialog_brush.green();
    blue_b = color_dialog_brush.blue();
    alpha_b = color_dialog_brush.alpha();

    pen_width = ui -> spinBox_Width -> value();
    pen_style = ui -> comboBox_line -> currentIndex();
    brush_style = ui -> comboBox_brush -> currentIndex();
    done(1);
}
void Dialog_style::on_pushButton_Cancel_clicked() //обработчик нажатия Cancel
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Внимание!", "Вы уверены, что хотите выйти? Все новые изменения не будут сохранены.", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        done(0);
    }
    else
    {
        return;
    }
}
void Dialog_style::closeEvent(QCloseEvent *event) //обработчик закрытия формы
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Внимание!", "Сохранить новые значения?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::Yes)
    {
        red_l = color_dialog_line.red();
        green_l = color_dialog_line.green();
        blue_l = color_dialog_line.blue();
        alpha_l = color_dialog_line.alpha();

        red_b = color_dialog_brush.red();
        green_b = color_dialog_brush.green();
        blue_b = color_dialog_brush.blue();
        alpha_b = color_dialog_brush.alpha();

        pen_width = ui -> spinBox_Width -> value();
        pen_style = ui -> comboBox_line -> currentIndex();
        brush_style = ui -> comboBox_brush -> currentIndex();
        done(1);
    }
    else
    {
        done(0);
        event -> accept();
    }
}

void Dialog_style::on_pushButton_colorLine_clicked() //выбор цвета заливки по кнопке
{
    // Обработчик получение нового цвета
    QColor color_temp_line = QColorDialog::getColor(Qt::white, this, "Выберите цвет линии",QColorDialog::ShowAlphaChannel);//получаем цвет линии при нажатии на соотв кнопку
    if(color_temp_line.isValid()) { //если значения выбрали
        color_dialog_line = color_temp_line;
        ui->pushButton_colorLine->setStyleSheet(QString("background-color: %1").arg(color_dialog_line.name()));//выводим его
    }
}
void Dialog_style::on_pushButton_colorBrush_clicked() //выбор цвета заливки по кнопке
{
    // Обработчик получение нового цвета
    QColor color_temp_brush = QColorDialog::getColor(Qt::white, this, "Выберите цвет залички",QColorDialog::ShowAlphaChannel);//получаем цвет линии при нажатии на соотв кнопку
    if(color_temp_brush.isValid()){//если значения выбрали
        color_dialog_brush = color_temp_brush;
        ui->pushButton_colorBrush->setStyleSheet(QString("background-color: %1").arg(color_dialog_brush.name()));//выводим его
    }
}

void Dialog_style::on_comboBox_line_currentIndexChanged(int index) //изменение комбобокса со стилями линий
{
    if(index == 0){
        ui -> pushButton_colorLine -> hide();
        ui ->label_width -> hide();
        ui -> spinBox_Width -> hide();
        ui -> label_line -> hide();
    }
    else{
        if(styleVisible == true){
            ui -> pushButton_colorLine -> show();
            ui ->label_width -> show();
            ui -> spinBox_Width -> show();
            if(index == 1){
                QPixmap myImage("D:/Sup_risov2/SolidLine.PNG");
                ui -> label_line ->setPixmap(myImage);
            }
            else if(index == 2){
                QPixmap myImage("D:/Sup_risov2/DashLine.PNG");
                ui -> label_line ->setPixmap(myImage);
            }
            else if(index == 3){
                QPixmap myImage("D:/Sup_risov2/DotLine.PNG");
                ui -> label_line ->setPixmap(myImage);
            }
            else if(index == 4){
                QPixmap myImage("D:/Sup_risov2/DashDotLine.PNG");
                ui -> label_line ->setPixmap(myImage);
            }
            else{
                QPixmap myImage("D:/Sup_risov2/DashDotDotLine.PNG");
                ui -> label_line ->setPixmap(myImage);
            }
        }
    }
}
void Dialog_style::on_comboBox_brush_currentIndexChanged(int index) //изменение комбобокса со стилями заливки
{
    if(index == 0 or styleBrushVisible == false){
        ui -> pushButton_colorBrush -> hide();
        ui -> label_brush -> hide();
    }
    else{
        ui -> pushButton_colorBrush -> show();
        ui -> label_brush -> show();
        if(index == 1){
            QPixmap myImageB(":/new/image/SolidPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 2){
            QPixmap myImageB(":/new/image/Danse1Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 3){
            QPixmap myImageB(":/new/image//Danse2Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 4){
            QPixmap myImageB(":/new/image/Danse3Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 5){
            QPixmap myImageB(":/new/image/Danse4Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 6){
            QPixmap myImageB(":/new/image/Danse5Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 7){
            QPixmap myImageB(":/new/image/Danse6Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 8){
            QPixmap myImageB(":/new/image/Danse7Pattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 9){
            QPixmap myImageB(":/new/image/HorPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 10){
            QPixmap myImageB(":/new/image/VerPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 11){
            QPixmap myImageB(":/new/image/CrossPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 12){
            QPixmap myImageB(":/new/image/BDiagPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else if(index == 13){
            QPixmap myImageB(":/new/image/FDiagPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
        else{
            QPixmap myImageB(":/new/image/DiagCrossPattern.PNG");
            ui -> label_brush ->setPixmap(myImageB);
        }
    }
}

