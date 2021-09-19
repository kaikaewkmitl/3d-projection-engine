#include "gl.h"

int main()
{
    Canvas c = newCanvas();

    c.drawLine(0, 0, 100, 100);

    std::cout << c.toString();
}