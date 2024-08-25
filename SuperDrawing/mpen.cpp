#include "mpen.h"

mpen::mpen() //конструктор
{
    pen_width = 1;
    pen_style = 1;
    brush_style = 1;
}
//СЕТТЕРЫ
bool mpen::SetWidth(int n_width)
{
    pen_width=n_width;
    return(true);
}
bool mpen::SetStyle(int n_style)
{
    pen_style=n_style;
    return(true);
}
bool mpen::SetStyleBrush(int b_style)
{
    brush_style = b_style;
    return(true);
}
//ГЕТТЕРЫ
int mpen::GetWidth(void)
{
    return(pen_width);
}
int mpen::GetStyle(void)
{
    return(pen_style);
}
int mpen::GetStyleBrush(void)
{
    return(brush_style);
}
