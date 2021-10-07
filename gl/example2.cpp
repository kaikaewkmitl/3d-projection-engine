// a program to demonstrate the usage of this
// gl by displaying a rotating cube

#include "gl.h"

void callback(Canvas *c);

struct Vector3D
{
    float x, y, z;
};

Vector3D rotate(Vector3D original, Vector3D rotation);
Vector3D translate(Vector3D original, Vector3D translation);
Vector3D centerScreen(Vector3D &i, float x, float y);
Vector3D project(Vector3D &i, double Z0);
void drawCube(std::vector<Vector3D> &vertices, Canvas *c);

// define a sub class that inherits
// from gl's Canvas class to set some
// additional attributes and assign
// calculated values in constructor
class Example2 : public Canvas
{
public:
    float Z0, width, height;
    Vector3D rotation = {0.0f, 0.0f, 0.0f};
    Vector3D pointOfRotation = {-25.0f, -25.0f, -25.0f};
    Vector3D zDistance = {0.0f, 0.0f, 1.0f};
    std::vector<Vector3D> vertices = {
        {0, 0, 0},
        {50, 0, 0},
        {0, 50, 0},
        {50, 50, 0},
        {0, 0, 50},
        {50, 0, 50},
        {0, 50, 50},
        {50, 50, 50},
    };

    Example2()
    {
        this->width = this->getCanvasWidth();
        this->height = this->getCanvasHeight();
        this->Z0 = this->width / tan((90.0f / 2.0f) * PI / 180.0f);

        for (int i = 0; i < 8; i++)
        {
            this->vertices[i] = translate(vertices[i], pointOfRotation);
        }
    }
};

int main()
{

    Example2 *e = new Example2();
    int exitStatus = e->mainloop(callback);
    delete e;

    std::cout << "program exitted with status " << exitStatus << std::endl;
}

void callback(Canvas *c)
{
    // typecast to (Example2 *) to be
    // able to access its attributes
    Example2 *e = (Example2 *)c;

    // this part contains the program logic
    // which will be run on every loop
    std::vector<Vector3D> newVertices(8);

    for (int i = 0; i < 8; i++)
    {
        newVertices[i] = rotate(e->vertices[i], e->rotation);
    }

    for (int i = 0; i < 8; i++)
    {
        newVertices[i] = translate(newVertices[i], e->zDistance);
    }

    for (int i = 0; i < 8; i++)
    {
        newVertices[i] = centerScreen(newVertices[i], e->width, e->height);
    }

    for (int i = 0; i < 8; i++)
    {
        newVertices[i] = project(newVertices[i], e->Z0);
    }

    drawCube(newVertices, e);

    e->rotation.y += 0.1f;
}

Vector3D rotate(Vector3D original, Vector3D rotation)
{
    Vector3D toReturn;

    // Rotation matrix: https://en.wikipedia.org/wiki/Rotation_matrix
    toReturn.x = original.x * (cos(rotation.z) * cos(rotation.y)) +
                 original.y * (cos(rotation.z) * sin(rotation.y) * sin(rotation.x) - sin(rotation.z) * cos(rotation.x)) +
                 original.z * (cos(rotation.z) * sin(rotation.y) * cos(rotation.x) + sin(rotation.z) * sin(rotation.x));
    toReturn.y = original.x * (sin(rotation.z) * cos(rotation.y)) +
                 original.y * (sin(rotation.z) * sin(rotation.y) * sin(rotation.x) + cos(rotation.z) * cos(rotation.x)) +
                 original.z * (sin(rotation.z) * sin(rotation.y) * cos(rotation.x) - cos(rotation.z) * sin(rotation.x));
    toReturn.z = original.x * (-sin(rotation.y)) +
                 original.y * (cos(rotation.y) * sin(rotation.x)) +
                 original.z * (cos(rotation.y) * cos(rotation.x));
    return toReturn;
}

Vector3D translate(Vector3D original, Vector3D translation)
{
    Vector3D toReturn;
    toReturn.x = original.x + translation.x;
    toReturn.y = original.y + translation.y;
    toReturn.z = original.z + translation.z;
    return toReturn;
}

Vector3D centerScreen(Vector3D &i, float x, float y)
{
    Vector3D toReturn;

    // random scaling
    toReturn.x = i.x + x / 2.0f;
    toReturn.y = i.y + y * 2.0f;
    toReturn.z = i.z;
    return toReturn;
}

Vector3D project(Vector3D &i, double Z0)
{
    Vector3D toReturn;
    toReturn.x = i.x * Z0 / (Z0 + i.z);
    toReturn.y = i.y * Z0 / (Z0 + i.z);
    toReturn.z = i.z;
    return toReturn;
}

void drawCube(std::vector<Vector3D> &vertices, Canvas *c)
{
    c->drawLine({vertices[0].x, vertices[0].y}, {vertices[1].x, vertices[1].y}, ColorRed);
    c->drawLine({vertices[0].x, vertices[0].y}, {vertices[2].x, vertices[2].y}, ColorRed);
    c->drawLine({vertices[0].x, vertices[0].y}, {vertices[4].x, vertices[4].y}, ColorRed);
    c->drawLine({vertices[1].x, vertices[1].y}, {vertices[3].x, vertices[3].y}, ColorRed);
    c->drawLine({vertices[1].x, vertices[1].y}, {vertices[5].x, vertices[5].y}, ColorRed);
    c->drawLine({vertices[2].x, vertices[2].y}, {vertices[3].x, vertices[3].y}, ColorRed);
    c->drawLine({vertices[2].x, vertices[2].y}, {vertices[6].x, vertices[6].y}, ColorRed);
    c->drawLine({vertices[3].x, vertices[3].y}, {vertices[7].x, vertices[7].y}, ColorRed);
    c->drawLine({vertices[4].x, vertices[4].y}, {vertices[5].x, vertices[5].y}, ColorRed);
    c->drawLine({vertices[4].x, vertices[4].y}, {vertices[6].x, vertices[6].y}, ColorRed);
    c->drawLine({vertices[5].x, vertices[5].y}, {vertices[7].x, vertices[7].y}, ColorRed);
    c->drawLine({vertices[6].x, vertices[6].y}, {vertices[7].x, vertices[7].y}, ColorRed);
}
