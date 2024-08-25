#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "mpen.h"
#include "tochka.h"
#include <QImage>
#include <QPainter>

class triangle
{
public:
    triangle();

    void draw(QImage &im);

    tochka t1;
    tochka t2;
    tochka t3;

    mpen pen;
};

#endif // TRIANGLE_H
