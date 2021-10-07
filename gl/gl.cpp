#include "gl.h"

#define BRAILLE_CHAR_OFFSET 10240
#define BRAILLE_CHAR_ROW 4
#define BRAILLE_CHAR_COL 2
#define CHAR_LIMIT 100
#define NEWLINE "\n"
#define COLOR_RESET "\033[m"
#define COLOR_FG(color) std::string("\033[38;5;") + std::to_string(color) + std::string("m")
#define COLOR_BG(color) std::string("\033[48;5;") + std::to_string(color) + std::string("m")
#define CLEAR_LINE "\033[2K"
#define CURSOR_HOME "\033[H"

const int pixelMap[BRAILLE_CHAR_ROW][BRAILLE_CHAR_COL] = {
    {1, 8},
    {2, 16},
    {4, 32},
    {64, 128},
};

bool programExit = false;

float toRadians(float deg)
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

void sortVecByY(std::vector<Vector2D> &v)
{
    std::sort(v.begin(), v.end(), [](Vector2D &v1, Vector2D &v2)
              { return v1.y < v2.y; });
}

std::string BrailleChar::toUnicode()
{
    std::string unicode = "";

    // apply black bg and specified fg color
    unicode += COLOR_BG(ColorBlack);
    unicode += COLOR_FG(this->color);

    // append braille char unicode
    std::wstring ws;
    ws += (wchar_t)(BRAILLE_CHAR_OFFSET + this->bChar);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    unicode += cvt.to_bytes(ws);

    unicode += COLOR_RESET;

    return unicode;
}

void BrailleChar::set(int x, int y, int color)
{
    int pixel = getPixel(x, y);
    int curCh = this->bChar;

    this->bChar = (curCh | pixel);
    this->color = color;
}

Canvas::Canvas()
{
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    this->width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
    this->height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#else
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    this->width = ws.ws_col;
    this->height = ws.ws_row;
#endif
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
    this->bCharMap.clear();

#if defined(_WIN32)
    const char *sh = getenv("SH");
    if (sh && std::string(sh) == "bash")
    {
        system("clear");
    }
    else
    {
        system("cls");
    }
#else
    system("clear");
#endif
}

void Canvas::overwriteCanvas()
{
    this->bCharMap.clear();

#if defined(_WIN32)
    const char *sh = getenv("SH");
    if (sh && std::string(sh) == "bash")
    {
        std::cout << CURSOR_HOME;
    }
    else
    {
        system("cls");
    }
#else
    std::cout << CURSOR_HOME;
#endif
}

int Canvas::getMaxY()
{
    int maxi = 0;
    for (auto i : this->bCharMap)
    {
        maxi = std::max(maxi, i.first);
    }

    return maxi * BRAILLE_CHAR_ROW;
}

int Canvas::getMinY()
{
    int mini = 0;
    for (auto i : this->bCharMap)
    {
        mini = std::min(mini, i.first);
    }

    return mini * BRAILLE_CHAR_ROW;
}

int Canvas::getMaxX()
{
    int maxi = 0;
    for (auto i : this->bCharMap)
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
    for (auto i : this->bCharMap)
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

void Canvas::setBChar(Vector2D v1, int color)
{
    int x = round(v1.x), y = round(v1.y);
    int posX = this->getPosX(x), posY = this->getPosY(y);
    this->bCharMap[posY][posX].set(x, y, color);
}

void Canvas::drawLine(Vector2D v1, Vector2D v2, int color)
{
    float diffX = abs(v1.x - v2.x), diffY = abs(v1.y - v2.y);
    float dirX, dirY;

    if (v1.x <= v2.x)
    {
        dirX = 1;
    }
    else
    {
        dirX = -1;
    }

    if (v1.y <= v2.y)
    {
        dirY = 1;
    }
    else
    {
        dirY = -1;
    }

    float diffMax = std::max(diffX, diffY);
    for (int i = 0; i < round(diffMax); i++)
    {
        float x = v1.x, y = v1.y;
        if (diffY != 0)
        {
            y += ((float)i * diffY) / (diffMax * dirY);
        }

        if (diffX != 0)
        {
            x += ((float)i * diffX) / (diffMax * dirX);
        }

        this->setBChar({x, y}, color);
    }
}

void Canvas::drawTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color)
{
    this->drawLine(v1, v2, color);
    this->drawLine(v2, v3, color);
    this->drawLine(v3, v1, color);
}

void Canvas::fillBottomFlatTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color)
{
    // need to find the change of x per y step
    // which is dx/dy, in other words an inverse slope
    float invSlope1 = (v2.x - v1.x) / (v2.y - v1.y);
    float invSlope2 = (v3.x - v1.x) / (v3.y - v1.y);
    float x1 = v1.x, x2 = v1.x;

    for (int y = v1.y; y <= v2.y; y++)
    {
        this->drawLine({x1, (float)y}, {x2, (float)y});
        x1 += invSlope1;
        x2 += invSlope2;
    }
}

void Canvas::fillTopFlatTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color)
{
    float invSlope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invSlope2 = (v3.x - v2.x) / (v3.y - v2.y);
    float x1 = v3.x, x2 = v3.x;

    for (int y = v3.y; y > v1.y; y--)
    {
        this->drawLine({x1, (float)y}, {x2, (float)y});
        x1 -= invSlope1;
        x2 -= invSlope2;
    }
}

void Canvas::fillTriangle(Vector2D v1, Vector2D v2, Vector2D v3, int color)
{
    std::vector<Vector2D> v = {v1, v2, v3};
    sortVecByY(v);

    if (v[1].y == v[2].y)
    {
        this->fillBottomFlatTriangle(v[0], v[1], v[2]);
    }
    else if (v[0].y == v[1].y)
    {
        this->fillTopFlatTriangle(v[0], v[1], v[2]);
    }
    else
    {
        float x4 = v[0].x + ((float)(v[1].y - v[0].y) / (float)(v[2].y - v[0].y)) * (v[2].x - v[0].x);
        float y4 = v[1].y;
        this->fillBottomFlatTriangle(v[0], v[1], {x4, y4});
        this->fillTopFlatTriangle(v[1], {x4, y4}, v[2]);
    }
}

std::vector<std::string> Canvas::getRows(int minX, int minY, int maxX, int maxY)
{
    int minRow = minY / BRAILLE_CHAR_ROW, maxRow = maxY / BRAILLE_CHAR_ROW;
    int minCol = minX / BRAILLE_CHAR_COL, maxCol = maxX / BRAILLE_CHAR_COL;
    std::vector<std::string> rows;

    for (int i = minRow; i <= maxRow; i++)
    {
        std::string row = "";

        for (int j = minCol; j <= maxCol; j++)
        {
            row += this->bCharMap[i][j].toUnicode();
        }

        rows.push_back(row);
    }

    return rows;
}

std::string Canvas::getDisplay(int minX, int minY, int maxX, int maxY)
{
    std::string frame = "";
    for (auto i : this->getRows(minX, minY, maxX, maxY))
    {
        frame += i;
        frame += NEWLINE;
    }

    return frame;
}

void Canvas::display()
{
    std::cout << this->getDisplay(this->getMinX(), this->getMinY(), this->getMaxX(), this->getMaxY());
}

int Canvas::mainloop(std::function<void(Canvas *)> callback)
{
    this->clearCanvas();
    while (true)
    {
        callback(this);

        this->display();
        usleep(100000);
        // this->overwriteCanvas();
        this->clearCanvas();

        signal(SIGINT, [](int sig)
               { programExit = true; });

        if (programExit)
        {
            std::cout << CLEAR_LINE;
            return PROGRAM_EXIT_SUCCESS;
        }
    }

    return PROGRAM_EXIT_FAIL;
}