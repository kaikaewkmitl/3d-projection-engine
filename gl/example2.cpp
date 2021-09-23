// a program to demonstrate the usage of this
// gl by displaying a simple animated graph

#include "gl.h"

// callback function definition
void callback(Canvas *c);

// define a sub class that inherits
// from gl's Canvas class to set some
// additional attributes (ie, bool first
// and vector<int> v). An alternative
// would be to declare those as global
class Example2 : public Canvas
{
public:
    bool first = true;
    std::vector<int> v;

    Example2() : v(100) {}
};

int main()
{

    Example2 *e = new Example2();
    int exitStatus = e->mainloop(callback);
    delete e;

    std::cout << "program exitted with status " << exitStatus << std::endl;
}

void callback(Canvas *c)
{
    // typecast to (Example2 *) to be
    // able to access its attributes
    Example2 *e = (Example2 *)c;

    // this part contains the program logic
    // which will be run on every loop
    if (e->first)
    {
        e->first = 0;
        for (int x = 0; x < 100; x++)
        {
            int y;
            if (x < 50)
                y = x;
            else
                y = 50 + (49 - x);

            // draw a BChar at position (x,y) with color red
            c->setBChar({(float)x, (float)y}, ColorRed);
            e->v[x] = y;
        }
    }
    else
    {
        std::vector<int> tmp(100);
        for (int x = 0; x < 100; x++)
        {
            tmp[x] = e->v[(x + 1) % 100];
            c->setBChar({(float)x, (float)tmp[x]}, ColorRed);
        }

        e->v = tmp;
    }
}