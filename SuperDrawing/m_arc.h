#ifndef M_ARC_H
#define M_ARC_H

#include "mpen.h"
#include "tochka.h"
#include <QImage>
#include <QPainter>

class m_arc
{
public:
    m_arc();
    void draw(QImage &im);

    tochka center;
    tochka radius;
    tochka radius2;
    tochka angle;

    mpen pen;  
};

#endif // M_ARC_H
