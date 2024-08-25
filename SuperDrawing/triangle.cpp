#include "triangle.h"

triangle::triangle() //конструктор
{

}

void triangle::draw(QImage &im)//рисование треугольника
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
    int x1,x2,y1,y2,x3,y3;
    t1.GetXY(x1,y1);
    t2.GetXY(x2,y2);
    t3.GetXY(x3,y3);
    QPointF p1(x1,y1);
    QPointF p2(x2,y2);
    QPointF p3(x3,y3);
    QPolygonF dr;
    dr << p1 << p2 << p3;

    painter.drawPolygon(dr);
}
