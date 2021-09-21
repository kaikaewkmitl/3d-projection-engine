#include "gl.h"

void callback(Canvas *c);

class Engine : public Canvas
{
public:
    bool first = true;
    std::vector<int> v;

    Engine() : v(100) {}
};

int main()
{

    Engine *e = new Engine();
    e->mainloop(callback);
    delete e;
}

void callback(Canvas *c)
{
    Engine *e = (Engine *)c;

    if (e->first)
    {
        e->first = 0;
        for (int i = 0; i < 100; i++)
        {
            int y;
            if (i < 50)
                y = i;
            else
                y = 50 + (49 - i);

            c->setBChar(i, y, ColorRed);
            e->v[i] = y;
        }
    }
    else
    {
        std::vector<int> tmp(100);
        for (int i = 0; i < 100; i++)
        {
            tmp[i] = e->v[(i + 1) % 100];
            c->setBChar(i, tmp[i], ColorRed);
        }

        e->v = tmp;
    }
}