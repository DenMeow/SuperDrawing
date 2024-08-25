#include "m_arc.h"

m_arc::m_arc() //конструктор
{

}


void m_arc::draw(QImage &im) //рисуем дугу
{
    QPainter painter(&im);
    QColor color;
    QPen qpen;
    int r,g,b,a;

    //настройки линии
    pen.GetRGBA(r,g,b,a);
    color.setRgb(r,g,b,a);
    qpen.setWidth(pen.GetWidth());
    qpen.setColor(color);
    qpen.setStyle(Qt::PenStyle(pen.GetStyle()));

    painter.setPen(qpen);
    int x,y,h,w,st,sp;
    center.GetXY(x, y);
    radius.GetStRadius(w);
    radius2.GetSpRadius(h);
    angle.GetAngle(st,sp);

//    if(st > sp){
//        painter.drawArc(x-w,y-h, w*2, h*2, sp*16, -(360*16 - (st*16-sp*16)));
//    }
//    else {
//        painter.drawArc(x-w,y-h, w*2, h*2, st*16,sp*16-st*16);
//    }
    painter.drawArc(x-w,y-h, w*2, h*2, st*16,sp*16-st*16);
}
