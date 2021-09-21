#ifndef GL_H
#define GL_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <codecvt>
#include <unistd.h>
#include <functional>

#if defined(_WIN32)
#include <windows.h>
#include <locale>
#else
#include <sys/ioctl.h>
#endif

// some colors index from
// ANSI 256 color code
enum eColorCode
{
    ColorBlack,
    ColorMaroon,
    ColorGreen,
    ColorOlive,
    ColorNavy,
    ColorPurple,
    ColorTeal,
    ColorSilver,
    ColorGrey,
    ColorRed,
    ColorLime,
    ColorYellow,
    ColorBlue,
    ColorFuchsia,
    ColorAqua,
    ColorWhite,

    // greyscale gradient can be obtained
    // by a number between 232 - 255
    ColorGreyScaleBlack = 232,
    ColorGreyScaleWhite = 255,
};

float toRadians(float deg);

int getPixel(int x, int y);

struct BrailleChar
{
    int bChar, color;

    std::string toUnicode();

    void set(int x, int y, int color);
};

class Canvas
{
private:
    int width, height;

    // maps position [y][x] to a given BrailleChar
    std::map<int, std::map<int, BrailleChar>> bCharMap;

    void clearCanvas();

    int getMaxY();

    int getMinY();

    int getMaxX();

    int getMinX();

    int getPosY(int y);

    int getPosX(int x);

    std::vector<std::string> getRows(int minX, int minY, int maxX, int maxY);

    std::string getDisplay(int minX, int minY, int maxX, int maxY);

    void display();

    void exit();

public:
    Canvas();

    int getCanvasWidth();

    int getCanvasHeight();

    void setBChar(int x, int y, int color = ColorWhite);

    void drawLine(float x1, float y1, float x2, float y2, int color = ColorWhite);

    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int color = ColorWhite);

    void mainloop(std::function<void(Canvas *)> callback);
};

#endif