#include "gl.h"

void callback(Canvas *c);

class Example3 : public Canvas
{
public:
    float xCoor[100];
    float yCoor[100];

    Example3()
    {
        for (int i = 0; i < 100; i++)
        {
            this->xCoor[i] = (i + 1) * (PI / (float)50);
            this->yCoor[i] = sinf(this->xCoor[i]);
        }
    }
};

int main()
{
    Example3 *e = new Example3();
    int exitStatus = e->mainloop(callback);
    delete e;

    std::cout << "program exitted with status " << exitStatus << std::endl;
}

void callback(Canvas *c)
{
    Example3 *e = (Example3 *)c;

    for (int i = 0; i < 100; i++)
    {
        // float y = sinf(x);
        e->setBChar({e->xCoor[i] * 30, e->yCoor[i] * 30}, ColorRed);
    }

    float tmp = e->yCoor[99];
    for (int i = 99; i > 0; i--)
    {
        e->yCoor[i] = e->yCoor[i - 1];
    }

    e->yCoor[0] = tmp;
}