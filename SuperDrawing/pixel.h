#ifndef PIXEL_H
#define PIXEL_H
#include"mpen.h"
#include "color.h"
#include "tochka.h"
#include <QImage>
#include <QPainter>

class pixel : public tochka, public color
{
public:
    pixel();

    void draw(QImage &im);
    mpen pen;
};

#endif // PIXEL_H
