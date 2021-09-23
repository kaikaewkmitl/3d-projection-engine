// a program to demonstrate the usage of
// this gl by displaying a filled triangle

#include "gl.h"

// define a sub class that inherits
// from gl's Canvas class to set some
// additional attributes (ie, v1,v2
// and v3). An alternative would be
// to declare those as global
class Example1 : public Canvas
{
public:
    Vector2D v1, v2, v3;

    Example1()
    {
        v1 = {100.0f, 30.0f};
        v2 = {75.0f, 10.0f};
        v3 = {100.0f, 50.0f};
    }
};

void callback(Canvas *c);

int main()
{

    Example1 *e = new Example1();

    // passes callback function
    // to mainloop so that the
    // logic gets executed on every loops
    int exitStatus = e->mainloop(callback);
    delete e;

    std::cout << "program exitted with status " << exitStatus << std::endl;
}

void callback(Canvas *c)
{
    // typecast to (Example1 *) to be
    // able to access its attributes
    Example1 *e = (Example1 *)c;

    // this part contains the program logic
    // which will be run on every loop
    e->fillTriangle(e->v1, e->v2, e->v3);
}