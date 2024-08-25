#ifndef CHORD_H
#define CHORD_H

#include "mpen.h"

#include "tochka.h"
#include <QImage>
#include <QPainter>

class chord
{
public:
    chord();
    void draw(QImage &im);

    tochka center;
    tochka radius;
    tochka radius2;
    tochka angle;

    mpen pen;
};

#endif // CHORD_H
