#include "gl.h"

double toRadians(double deg)
{
    return deg * (PI / 180);
}

int getPixel(int x, int y)
{
    if (y >= 0)
    {
        y %= BRAILLE_CHAR_ROW;
    }
    else
    {
        y = (BRAILLE_CHAR_ROW - 1) + ((y + 1) % BRAILLE_CHAR_ROW);
    }

    if (x >= 0)
    {
        x %= BRAILLE_CHAR_COL;
    }
    else
    {
        x = (BRAILLE_CHAR_COL - 1) + ((x + 1) % BRAILLE_CHAR_COL);
    }

    return pixelMap[y][x];
}

Canvas newCanvas()
{
    Canvas canv = Canvas();
    return canv;
}

int Canvas::getCanvasWidth()
{
    return this->width * BRAILLE_CHAR_COL;
}

int Canvas::getCanvasHeight()
{
    return this->height;
}

void Canvas::clearCanvas()
{
    this->charsMap.clear();

#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}