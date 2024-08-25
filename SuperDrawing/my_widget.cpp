#include "my_widget.h"
#include<QMessageBox>

my_widget::my_widget(QWidget *parent) : QWidget(parent) //конструктор
{
    im_created=false;
}

void my_widget::paintEvent(QPaintEvent *) //событие перерисовки
{
    if (im_created)
    {
        QPainter painter(this);
        painter.drawImage(0,0,im);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Изображение не было создано!");
    }
}

void my_widget::create_im(int size_x, int size_y) //инициализация изображения
{
    im = QImage(size_x,size_y,QImage::Format_ARGB32_Premultiplied);
    im_created=true;
}
