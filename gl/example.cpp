#include "gl.h"

bool first = 1;
std::vector<int> v(100);

void callback(Canvas *c);

int main()
{
    Canvas *c = new Canvas();
    c->mainloop(callback);
    delete c;
}

void callback(Canvas *c)
{

    if (first)
    {
        first = 0;
        for (int i = 0; i < 100; i++)
        {
            int y;
            if (i < 50)
                y = i;
            else
                y = 50 + (49 - i);

            c->setBChar(i, y, ColorRed);
            v[i] = y;
        }
    }
    else
    {
        std::vector<int> tmp(100);
        for (int i = 0; i < 100; i++)
        {
            tmp[i] = v[(i + 1) % 100];
            c->setBChar(i, tmp[i], ColorRed);
        }

        v = tmp;
    }
}