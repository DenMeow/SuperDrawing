#ifndef LINE_H
#define LINE_H

#include "mpen.h"
#include "tochka.h"
#include <QImage>
#include <QPainter>

class line
{
public:
    line();
    void draw(QImage &im);

    tochka st;
    tochka end;

    mpen pen;
};

#endif // LINE_H
