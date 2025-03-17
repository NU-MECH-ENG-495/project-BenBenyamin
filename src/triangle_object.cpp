#include "triangle_object.h"
#include "triangle.h"
#include "canvas.h"
#include "stl.h"
TriangleObject::TriangleObject(const std::string &stlFileName)
{
    triangles = std::make_shared<std::vector<TriangleSurface>>();
    readSTL(stlFileName, triangles);
}

void TriangleObject::project(Canvas &c)
{
    for (int i = 0; i < triangles->size(); ++i)
    {
        (*triangles)[i].project(c);
    }
}

void TriangleObject::rotateAroundX(float angle, const std::vector<float> &rotationPoint)
{
    #pragma omp parallel for
    for (int i = 0; i < triangles->size(); ++i)
    {
        (*triangles)[i].rotateAroundX(angle, rotationPoint);
    }
}

void TriangleObject::rotateAroundY(float angle, const std::vector<float> &rotationPoint)
{
    #pragma omp parallel for
    for (int i = 0; i < triangles->size(); ++i)
    {
        (*triangles)[i].rotateAroundY(angle, rotationPoint);
    }
}

void TriangleObject::rotateAroundZ(float angle, const std::vector<float> &rotationPoint)
{
    #pragma omp parallel for
    for (int i = 0; i < triangles->size(); ++i)
    {
        (*triangles)[i].rotateAroundZ(angle, rotationPoint);
    }
}

void TriangleObject::scale(float k)
{
    #pragma omp parallel for
    for (int i = 0; i < triangles->size(); ++i)
    {
        (*triangles)[i].scale(k);
    }
}

void TriangleObject::translate(float x, float y, float z)
{
    #pragma omp parallel for
    for (int i = 0; i < triangles->size(); ++i)
    {
        (*triangles)[i].translate(x, y, z);
    }
}

int TriangleObject::size()
{
    return static_cast<int>(triangles->size());
}
