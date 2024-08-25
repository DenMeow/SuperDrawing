#ifndef POLYGON_H
#define POLYGON_H


#include "mpen.h"
#include <QImage>
#include <QPainter>
#include <vector>

class polygon
{
public:
    polygon();
    void draw(QImage &im);

    QPointF point;
    QVector<QPointF> points;

    mpen pen;
};

#endif // POLYGON_H
