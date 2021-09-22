#include "gl.h"

class Example2 : public Canvas
{
public:
    Vector2D v1, v2, v3;

    Example2()
    {
        v1 = {100.0f, 30.0f};
        v2 = {75.0f, 10.0f};
        v3 = {100.0f, 50.0f};
    }
};

void cb(Canvas *c)
{
    Example2 *e = (Example2 *)c;
    e->fillTriangle(e->v1, e->v2, e->v3);
}

int main()
{
    Example2 *e = new Example2();
    e->mainloop(cb);
    delete e;
}