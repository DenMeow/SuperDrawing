#ifndef MPEN_H
#define MPEN_H

#include "color.h"


class mpen : public color
{
public:
    mpen();
    bool SetWidth(int n_width);
    int GetWidth(void);
    bool SetStyle(int n_style);
    int GetStyle(void);
    bool SetStyleBrush(int b_style);
    int GetStyleBrush(void);

protected:
    int pen_width;
    int pen_style;
    int brush_style;
};

#endif // MPEN_H
