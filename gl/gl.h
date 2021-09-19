#ifndef GL_H
#define GL_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <codecvt>
#include <unistd.h>

#if defined(_WIN32)
#include <windows.h>
#include <locale>
#else
#include <sys/ioctl.h>
#endif

#define PI 3.14159
#define BRAILLE_CHAR_OFFSET 10240
#define BRAILLE_CHAR_ROW 4
#define BRAILLE_CHAR_COL 2
#define CHAR_LIMIT 100
#define NEWLINE "\n"

const int pixelMap[BRAILLE_CHAR_ROW][BRAILLE_CHAR_COL] = {
    {1, 8},
    {2, 16},
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
    Canvas();

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

    void drawLine(double x1, double y1, double x2, double y2, int color = 255);

    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int color = 255);

    std::string getUnicode(Char ch);

    std::vector<std::string> getRows(int minX, int minY, int maxX, int maxY);

    std::string getFrame(int minX, int minY, int maxX, int maxY);

    std::string toString();
};

Canvas newCanvas();

#endif