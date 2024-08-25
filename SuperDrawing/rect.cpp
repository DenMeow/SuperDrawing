#include "rect.h"

mrect::mrect()// конструктор
{

}

void mrect::draw(QImage &im)//рисование прямоугольника
{
    QPainter painter(&im);
    QColor color;
    QPen qpen;
    QBrush qbrush;
    int r,g,b,a,r_b,g_b,b_b,a_b;
    //настройки линии
    pen.GetRGBA(r,g,b,a);
    color.setRgb(r,g,b,a);
    qpen.setWidth(pen.GetWidth());
    qpen.setColor(color);
    qpen.setStyle(Qt::PenStyle(pen.GetStyle()));

    //настройки заливки
    pen.GetRGBA_brush(r_b,g_b,b_b,a_b);
    color.setRgb(r_b,g_b,b_b,a_b);
    qbrush.setColor(color);
    qbrush.setStyle(Qt::BrushStyle(pen.GetStyleBrush()));

    painter.setPen(qpen);
    painter.setBrush(qbrush);
    int x1,x2,y1,y2;
    left_top.GetXY(x1,y1);
    right_bottom.GetXY(x2,y2);
    painter.drawRect(x1,y1,x2-x1,y2-y1);
}
