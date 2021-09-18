#ifndef GL_H
#define GL_H

#include <iostream>
#include <string>
#include <map>

#define PI 3.14159
#define BRAILLE_CHAR_OFFSET 2800
#define BRAILLE_CHAR_ROW 4
#define BRAILLE_CHAR_COL 2

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
    std::string lineEnding;
    std::map<int, std::map<int, Char> > charsMap;

public:
    Canvas() : lineEnding("\n")
    {
    }

    int getCanvasWidth();

    int getCanvasHeight();
};

Canvas newCanvas();

#endif