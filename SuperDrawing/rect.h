#ifndef RECT_H
#define RECT_H

#include "mpen.h"
#include "tochka.h"
#include <QImage>
#include <QPainter>

class mrect
{
public:
    mrect();

    void draw(QImage &im);

    tochka left_top;
    tochka right_bottom;

    mpen pen;
};

#endif // RECT_H
