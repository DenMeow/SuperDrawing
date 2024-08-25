#include "color.h"

color::color() //конструктор
{
    red_l=0;
    green_l=0;
    blue_l=0;
    alpha_l=255;

    red_b=0;
    green_b=0;
    blue_b=0;
    alpha_b=255;
}
//сеттер
bool color::SetRGBA(int r, int g, int b, int a)
{
    red_l=r;
    green_l=g;
    blue_l=b;
    alpha_l=a;
    return (true);

}
bool color::SetRGBA_brush(int r_b, int g_b, int b_b, int a_b){
    red_b=r_b;
    green_b=g_b;
    blue_b=b_b;
    alpha_b=a_b;
    return (true);
}
//геттер
void color::GetRGBA(int &r, int &g, int &b, int &a)
{
    r=red_l;
    g=green_l;
    b=blue_l;
    a=alpha_l;
}
void color::GetRGBA_brush(int &r_b, int &g_b, int &b_b, int &a_b){
    r_b=red_b;
    g_b=green_b;
    b_b=blue_b;
    a_b=alpha_b;
}
