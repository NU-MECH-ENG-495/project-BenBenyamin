#include "triangle_object.h"
#include "canvas.h"

TriangleObject::TriangleObject(const std::string &stlFileName)
{
    triangles = std::make_shared<std::vector<TriangleSurface>>();
}

void TriangleObject::project(Canvas &c)
{
}

void TriangleObject::rotateAroundX(float angle, const std::vector<float> &rotationPoint)
{
}

void TriangleObject::rotateAroundY(float angle, const std::vector<float> &rotationPoint)
{
}

void TriangleObject::rotateAroundZ(float angle, const std::vector<float> &rotationPoint)
{
}

void TriangleObject::scale(float k)
{
}

void TriangleObject::translate(float x, float y, float z)
{
}

int TriangleObject::size()
{
    return static_cast<int>(triangles->size());
}
