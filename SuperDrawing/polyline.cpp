#include "polyline.h"

polyline::polyline()//конструктор
{

}

void polyline::draw(QImage &im) { //рисование ломанной линии
    QPainter painter(&im);
    QColor color;
    QPen qpen;
    QBrush qbrush;
    int r,g,b,a;

    //настройки линии
    pen.GetRGBA(r,g,b,a);
    color.setRgb(r,g,b,a);
    qpen.setWidth(pen.GetWidth());
    qpen.setColor(color);
    qpen.setStyle(Qt::PenStyle(pen.GetStyle()));

    painter.setPen(qpen);
    painter.drawPolyline(points);
}
