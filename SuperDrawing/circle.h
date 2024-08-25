#ifndef CIRCLE_H
#define CIRCLE_H

#include "mpen.h"

#include "tochka.h"
#include <QImage>
#include <QPainter>

class circle
{
public:
    circle();

    void draw(QImage &im);

    tochka center;
    tochka radius;

    mpen pen;
    mpen pen_b;
};

#endif // CIRCLE_H
