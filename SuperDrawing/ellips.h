#ifndef ELLIPS_H
#define ELLIPS_H

#include "mpen.h"
#include "tochka.h"
#include <QImage>
#include <QPainter>

class ellips
{
public:
    ellips();

    void draw(QImage &im);

    tochka center;
    tochka radius;

    mpen pen;
};

#endif // ELLIPS_H
