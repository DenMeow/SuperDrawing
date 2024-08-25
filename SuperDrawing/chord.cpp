#include "chord.h"

chord::chord()//конструктор
{

}
void chord::draw(QImage &im) //рисуем сегмент
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
    int x,y,h,w,st,sp;
    center.GetXY(x, y);
    radius.GetStRadius(w);
    radius2.GetSpRadius(h);
    angle.GetAngle(st,sp);

    painter.drawChord(x-w,y-h, w*2, h*2, st*16,sp*16-st*16);
}
