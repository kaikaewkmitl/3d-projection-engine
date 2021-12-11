#include "../gl/gl.h"

void callback(Canvas *c);

struct Vector3D
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Triangle
{
    Vector3D p[3];
};

struct Mesh
{
    std::vector<Triangle> tris;
};

struct Matrix4X4
{
    float mat[4][4] = {0.0f};
};

class Engine : public Canvas
{
public:
    Mesh cube;
    Matrix4X4 matProjection, matRotationX, matRotationZ;
    float height, width, near, far, fov, fovRad, aspectRatio, inc;

    Engine()
    {
        this->height = this->getCanvasHeight() * 2.0f;
        this->width = this->getCanvasWidth();

        this->cube.tris = {
            {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        };

        this->near = 0.1f;
        this->far = 1000.0f;
        this->fov = 90.0f;
        this->fovRad = 1.0f / tanf(this->fov * 0.5f / 180.0f * PI);
        this->aspectRatio = (float)this->height / (float)this->width;
        this->inc = 0.0f;

        this->matProjection.mat[0][0] = this->aspectRatio * this->fovRad;
        this->matProjection.mat[1][1] = this->fovRad;
        this->matProjection.mat[2][2] = this->far / (this->far - this->near);
        this->matProjection.mat[3][2] = (-this->far * this->near) / (this->far - this->near);
        this->matProjection.mat[2][3] = 1.0f;
        this->matProjection.mat[3][3] = 0.0f;
    }
};

void multiplyMatrixVector(Vector3D &i, Vector3D &o, Matrix4X4 &m)
{
    o.x = i.x * m.mat[0][0] + i.y * m.mat[1][0] + i.z * m.mat[2][0] + m.mat[3][0];
    o.y = i.x * m.mat[0][1] + i.y * m.mat[1][1] + i.z * m.mat[2][1] + m.mat[3][1];
    o.z = i.x * m.mat[0][2] + i.y * m.mat[1][2] + i.z * m.mat[2][2] + m.mat[3][2];

    float w = i.x * m.mat[0][3] + i.y * m.mat[1][3] + i.z * m.mat[2][3] + m.mat[3][3];
    if (w != 0.0f)
    {
        o.x /= w;
        o.y /= w;
        o.z /= w;
    }
}

int main()
{
    Engine *e = new Engine();
    int exitStatus = e->mainloop(callback);
    delete e;

    std::cout << "program exitted with status " << exitStatus << std::endl;
}

void callback(Canvas *c)
{
    Engine *e = (Engine *)c;

    float theta = 1.0f + e->inc;
    e->matRotationZ.mat[0][0] = cosf(theta);
    e->matRotationZ.mat[0][1] = sinf(theta);
    e->matRotationZ.mat[1][0] = -sinf(theta);
    e->matRotationZ.mat[1][1] = cosf(theta);
    e->matRotationZ.mat[2][2] = 1.0f;
    e->matRotationZ.mat[3][3] = 1.0f;

    e->matRotationX.mat[0][0] = 1.0f;
    e->matRotationX.mat[1][1] = cosf(theta * 0.5f);
    e->matRotationX.mat[1][2] = sinf(theta * 0.5f);
    e->matRotationX.mat[2][1] = -sinf(theta * 0.5f);
    e->matRotationX.mat[2][2] = cosf(theta * 0.5f);
    e->matRotationX.mat[3][3] = 1.0f;

    std::vector<Triangle> sortedTris;

    for (auto &tri : e->cube.tris)
    {
        Triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

        // rotate around z-axis
        multiplyMatrixVector(tri.p[0], triRotatedZ.p[0], e->matRotationZ);
        multiplyMatrixVector(tri.p[1], triRotatedZ.p[1], e->matRotationZ);
        multiplyMatrixVector(tri.p[2], triRotatedZ.p[2], e->matRotationZ);

        // rotate around x-axis
        multiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], e->matRotationX);
        multiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], e->matRotationX);
        multiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], e->matRotationX);

        // how far away the cube is
        triTranslated = triRotatedZX;
        triTranslated.p[0].z += 2.5f;
        triTranslated.p[1].z += 2.5f;
        triTranslated.p[2].z += 2.5f;

        Vector3D normal, l1, l2;
        l1.x = triTranslated.p[1].x - triTranslated.p[0].x;
        l1.y = triTranslated.p[1].y - triTranslated.p[0].y;
        l1.z = triTranslated.p[1].z - triTranslated.p[0].z;

        l2.x = triTranslated.p[2].x - triTranslated.p[0].x;
        l2.y = triTranslated.p[2].y - triTranslated.p[0].y;
        l2.z = triTranslated.p[2].z - triTranslated.p[0].z;

        normal.x = l1.y * l2.z - l1.z * l2.y;
        normal.y = l1.z * l2.x - l1.x * l2.z;
        normal.z = l1.x * l2.y - l1.y * l2.x;

        // normalize normal into unit vector
        float magnitude = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x /= magnitude;
        normal.y /= magnitude;
        normal.z /= magnitude;

        float dotProduct = normal.x * triTranslated.p[0].x + normal.y * triTranslated.p[0].y + normal.z * triTranslated.p[0].z;
        if (dotProduct < 0.0f)
        {
            multiplyMatrixVector(triTranslated.p[0], triProjected.p[0], e->matProjection);
            multiplyMatrixVector(triTranslated.p[1], triProjected.p[1], e->matProjection);
            multiplyMatrixVector(triTranslated.p[2], triProjected.p[2], e->matProjection);

            triProjected.p[0].x += 2.0f;
            triProjected.p[0].y += 2.0f;

            triProjected.p[1].x += 2.0f;
            triProjected.p[1].y += 2.0f;

            triProjected.p[2].x += 2.0f;
            triProjected.p[2].y += 2.0f;

            triProjected.p[0].x *= 0.25f * e->width;
            triProjected.p[1].x *= 0.25f * e->width;
            triProjected.p[2].x *= 0.25f * e->width;

            triProjected.p[0].y *= 0.5f * e->height;
            triProjected.p[1].y *= 0.5f * e->height;
            triProjected.p[2].y *= 0.5f * e->height;

            sortedTris.push_back(triProjected);
        }
    }

    std::sort(sortedTris.begin(), sortedTris.end(), [](Triangle &t1, Triangle &t2)
              {
                  float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                  float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
                  return z1 > z2;
              });

    for (auto &tri : sortedTris)
    {
        Vector2D v1 = {tri.p[0].x, tri.p[0].y};
        Vector2D v2 = {tri.p[1].x, tri.p[1].y};
        Vector2D v3 = {tri.p[2].x, tri.p[2].y};
        e->drawTriangle(v1, v2, v3);
    }

    e->inc += 0.3f;
}
