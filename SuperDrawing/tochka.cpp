#include "tochka.h"

tochka::tochka() //конструктор
{
    x=0;
    y=0;
    h = 0;
    w = 0;
    startAngle = 0;
    spanAngle = 0;
}
//сеттеры
void tochka::SetX(int new_x)
{
    x=new_x;
}
void tochka::SetY(int new_y)
{
    y=new_y;
}
void tochka::SetXY(int new_x, int new_y)
{
    x=new_x;
    y=new_y;
}
void tochka::SetStRadius(int new_stradius){
    h = new_stradius;
}
void tochka::SetSpRadius(int new_spradius){
    w = new_spradius;
}
void tochka::SetAngle(int new_startAngle, int new_spanAngle){
    startAngle = new_startAngle;
    spanAngle = new_spanAngle;
}

//геттеры
int tochka::GetX(void)
{
    return (x);
}
int tochka::GetY(void)
{
    return (y);
}
void tochka::GetXY(int &zn_x,int &zn_y)
{
    zn_x=x;
    zn_y=y;
}
void tochka::GetStRadius(int &zn_stradius){
    zn_stradius = h;
}
void tochka::GetSpRadius(int &zn_spradius){
    zn_spradius = w;
}
void tochka::GetAngle(int &zn_st, int &zn_sp){
    zn_st = startAngle;
    zn_sp = spanAngle;
}
