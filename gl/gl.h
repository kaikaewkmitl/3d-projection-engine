#ifndef GL_H
#define GL_H

#include <iostream>
#include <string>
#include <map>

#if defined(_WIN32)
#include <windows.h>
#include <locale>
#else
#include <sys/ioctl.h>
#endif

#define PI 3.14159
#define BRAILLE_CHAR_OFFSET 2800
#define BRAILLE_CHAR_ROW 4
#define BRAILLE_CHAR_COL 2
#define NEWLINE "\n"

const int pixelMap[BRAILLE_CHAR_ROW][BRAILLE_CHAR_COL] = {
    {1, 8},
    {2, 10},
    {4, 32},
    {64, 128},
};

double toRadians(double deg);

int getPixel(int x, int y);

struct Char
{
    int ch, color;
};

class Canvas
{
private:
    int width, height;

    // maps position [y][x] to a given Char
    std::map<int, std::map<int, Char>> charsMap;

public:
    Canvas()
    {
    }

    int getCanvasWidth();

    int getCanvasHeight();

    void clearCanvas();

    int getMaxY();

    int getMinY();

    int getMaxX();

    int getMinX();

    int getPosY(int y);

    int getPosX(int x);

    void setChar(int x, int y, int color);
};

Canvas newCanvas();

#endif