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

std::string BrailleChar::toUnicode()
{
    std::string unicode = "";

    // apply color
    char color[CHAR_LIMIT];
    sprintf(color, "\033[38;5;%dm", this->color);
    unicode += std::string(color);

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
    system("cls");
#else
    system("clear");
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

void Canvas::setBChar(int x, int y, int color)
{
    int posX = this->getPosX(x), posY = this->getPosY(y);
    this->bCharMap[posY][posX].set(x, y, color);
}

void Canvas::drawLine(double x1, double y1, double x2, double y2, int color)
{
    double diffX = abs(x1 - x2), diffY = abs(y1 - y2);
    double dirX, dirY;

    if (x1 <= x2)
    {
        dirX = 1;
    }
    else
    {
        dirX = -1;
    }

    if (y1 <= y2)
    {
        dirY = 1;
    }
    else
    {
        dirY = -1;
    }

    double diffMax = std::max(diffX, diffY);
    for (int i = 0; i < round(diffMax); i++)
    {
        double x = x1, y = y1;
        if (diffY != 0)
        {
            y += ((double)i * diffY) / (diffMax * dirY);
        }

        if (diffX != 0)
        {
            x += ((double)i * diffX) / (diffMax * dirX);
        }

        this->setBChar(round(x), round(y), color);
    }
}

void Canvas::drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int color)
{
    this->drawLine(x1, y1, x2, y2, color);
    this->drawLine(x2, y2, x3, y3, color);
    this->drawLine(x3, y3, x1, y1, color);
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

void Canvas::mainloop(std::function<void(Canvas *)> callback)
{
    while (true)
    {
        callback(this);

        this->display();
        usleep(100000);
        this->clearCanvas();
    }
}