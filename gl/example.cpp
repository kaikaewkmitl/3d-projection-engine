#include "gl.h"

void callback(Canvas *c);

class Example : public Canvas
{
public:
    bool first = true;
    std::vector<int> v;

    Example() : v(100) {}
};

int main()
{

    Example *e = new Example();
    e->mainloop(callback);

    delete e;
}

void callback(Canvas *c)
{
    // typecast to Example * to
    // obtain its attributes
    Example *e = (Example *)c;

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

            c->setBChar({(float)i, (float)y}, ColorRed);
            e->v[i] = y;
        }
    }
    else
    {
        std::vector<int> tmp(100);
        for (int i = 0; i < 100; i++)
        {
            tmp[i] = e->v[(i + 1) % 100];
            c->setBChar({(float)i, (float)tmp[i]}, ColorRed);
        }

        e->v = tmp;
    }
}