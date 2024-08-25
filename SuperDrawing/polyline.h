#ifndef POLYLINE_H
#define POLYLINE_H

#include "mpen.h"
//#include "tochka.h"
#include <QImage>
#include <QPainter>
#include <vector>

class polyline
{
public:
    polyline();
    void draw(QImage &im);

    QPointF point;
    QVector<QPointF> points;

    mpen pen;
};

#endif // POLYLINE_H
