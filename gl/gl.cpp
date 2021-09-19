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

int Canvas::getMaxY()
{
    int maxi = 0;
    for (auto i : this->charsMap)
    {
        maxi = std::max(maxi, i.first);
    }

    return maxi * BRAILLE_CHAR_ROW;
}

int Canvas::getMinY()
{
    int mini = 0;
    for (auto i : this->charsMap)
    {
        mini = std::min(mini, i.first);
    }

    return mini * BRAILLE_CHAR_ROW;
}

int Canvas::getMaxX()
{
    int maxi = 0;
    for (auto i : this->charsMap)
    {
        for (auto j : i.second)
        {
            maxi = std::max(maxi, j.first);
        }
    }

    return maxi * BRAILLE_CHAR_COL;
}

int Canvas::getMinX()
{
    int mini = 0;
    for (auto i : this->charsMap)
    {
        for (auto j : i.second)
        {
            mini = std::min(mini, j.first);
        }
    }

    return mini * BRAILLE_CHAR_COL;
}

int Canvas::getPosY(int y)
{
    return y / BRAILLE_CHAR_ROW;
}

int Canvas::getPosX(int x)
{
    return x / BRAILLE_CHAR_COL;
}

void Canvas::setChar(int x, int y, int color)
{
    int posX = this->getPosX(x), posY = this->getPosY(y);
    int curCh = this->charsMap[posY][posX].ch;
    int pixel = getPixel(x, y);

    this->charsMap[posY][posX].ch = (curCh | pixel);
    this->charsMap[posY][posX].color = color;
}
