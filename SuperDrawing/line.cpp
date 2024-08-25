#include "line.h"

line::line()// конструктор
{
}

void line::draw(QImage &im) //рисуем линию
{
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
    int x1,x2,y1,y2;
    st.GetXY(x1,y1);
    end.GetXY(x2,y2);
    painter.drawLine(x1,y1,x2,y2);
}
