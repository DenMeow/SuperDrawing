#ifndef TOCHKA_H
#define TOCHKA_H


class tochka
{
public:
    tochka();
    //координаты
    void SetX(int new_x);
    void SetY(int new_y);
    void SetXY(int new_x, int new_y);
    int GetX(void);
    int GetY(void);
    void GetXY(int &zn_x,int &zn_y);
    //углы
    void SetStRadius(int new_stradius);
    void SetSpRadius(int new_spradius);
    void SetAngle(int new_startAngle, int new_spanAngle);
    void GetStRadius(int &zn_stradius);
    void GetSpRadius(int &zn_spradius);
    void GetAngle(int &zn_st, int &zn_sp);

protected:
    int x;
    int y;
    int h;
    int w;
    int startAngle;
    int spanAngle;

};

#endif // TOCHKA_H
