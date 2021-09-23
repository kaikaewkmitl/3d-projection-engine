#ifndef GL_H
#define GL_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <codecvt>
#include <unistd.h>
#include <functional>
#include <algorithm>

#if defined(_WIN32)
#include <windows.h>
#include <locale>
#else
#include <sys/ioctl.h>
#endif

// the first 16 color and
// the greyscale code
// defined in ANSI 256 colors
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

// this gl uses Braille characters
// to display everything instead of
// pixel since terminal are
// character-cell displays
struct BrailleChar
{
    int bChar, color;

    std::string toUnicode();

    void set(int x, int y, int color = ColorWhite);
};

struct Vector2D
{
    float x, y;
};

// sort a vector of Vector2D by y in ascending order
void sortVecByY(std::vector<Vector2D> &v);

class Canvas
{
private:
    int width, height;

    // maps position [y][x] to a given BrailleChar
    std::unordered_map<int, std::unordered_map<int, BrailleChar>> bCharMap;

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

    void fillBottomFlatTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color = ColorWhite);

    void fillTopFlatTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color = ColorWhite);

public:
    Canvas();

    int getCanvasWidth();

    int getCanvasHeight();

    // sets a Braille Character at the position (x,y)
    // with the color specified. If the color is not
    // specified, it is white by default
    void setBChar(Vector2D v1, int color = ColorWhite);

    void drawLine(Vector2D v1, Vector2D v2, int color = ColorWhite);

    void drawTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color = ColorWhite);

    void fillTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color = ColorWhite);

    // mainloop takes a callback function as a parameter
    // which will be called on every loop until there is
    // interrupt signal (Ctrl + C)
    void mainloop(std::function<void(Canvas *)> callback);
};

#endif