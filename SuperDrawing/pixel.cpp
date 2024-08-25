#include "pixel.h"

pixel::pixel() //конструктор
{

}

void pixel::draw(QImage &im) //рисование пикселя
{
    QPainter painter(&im);
    QColor color;

    int r,g,b,a;
    pen.GetRGBA(r,g,b,a);

    color.setRgb(r,g,b,a);

    QPen qpen;
    qpen.setWidth(pen.GetWidth());
    qpen.setColor(color);

    painter.setPen(qpen);
    painter.drawPoint(x,y);
}
