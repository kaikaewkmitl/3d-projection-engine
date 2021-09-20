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

#define PI 3.14159
#define BRAILLE_CHAR_OFFSET 10240
#define BRAILLE_CHAR_ROW 4
#define BRAILLE_CHAR_COL 2
#define CHAR_LIMIT 100
#define NEWLINE "\n"
#define COLOR_RESET "\033[m"

const int pixelMap[BRAILLE_CHAR_ROW][BRAILLE_CHAR_COL] = {
    {1, 8},
    {2, 16},
    {4, 32},
    {64, 128},
};

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

double toRadians(double deg);

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

public:
    Canvas();

    void exit();

    int getCanvasWidth();

    int getCanvasHeight();

    void clearCanvas();

    int getMaxY();

    int getMinY();

    int getMaxX();

    int getMinX();

    int getPosY(int y);

    int getPosX(int x);

    void setBChar(int x, int y, int color = ColorWhite);

    void drawLine(double x1, double y1, double x2, double y2, int color = ColorWhite);

    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int color = ColorWhite);

    std::vector<std::string> getRows(int minX, int minY, int maxX, int maxY);

    std::string getDisplay(int minX, int minY, int maxX, int maxY);

    void display();

    void mainloop(std::function<void(Canvas *)> callback);
};

#endif