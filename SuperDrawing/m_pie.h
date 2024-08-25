#ifndef M_PIE_H
#define M_PIE_H

#include "mpen.h"

#include "tochka.h"
#include <QImage>
#include <QPainter>

class m_pie
{
public:
    m_pie();
    void draw(QImage &im);

    tochka center;
    tochka radius;
    tochka radius2;
    tochka angle;

    mpen pen;
};

#endif // M_PIE_H
