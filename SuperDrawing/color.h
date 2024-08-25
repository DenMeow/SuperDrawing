#ifndef COLOR_H
#define COLOR_H

class color
{
public:
    color();
    bool SetRGBA(int r, int g, int b, int a);
    void GetRGBA(int &r, int &g, int &b, int &a);

    bool SetRGBA_brush(int r_b, int g_b, int b_b, int a_b);
    void GetRGBA_brush(int &r_b, int &g_b, int &b_b, int &a_b);

protected:
    int red_l;
    int green_l;
    int blue_l;
    int alpha_l;

    int red_b;
    int green_b;
    int blue_b;
    int alpha_b;
};

#endif // COLOR_H
