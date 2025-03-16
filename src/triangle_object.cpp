#include <omp.h>
#include "triangle_object.h"
#include "stl.h"
#include "canvas.h"

TriangleObject::TriangleObject(const std::string &stlFileName)
{
    this->triangles = readSTL(stlFileName);
    this->length = this->triangles->size();
}

void TriangleObject::rotateAroundX(float angle, const std::vector<float> &rotationPoint)
{   
    for (int i = 0; i < length; i++)
    {
        this->triangles->at(i).rotateAroundX(angle, rotationPoint);
    }
}

void TriangleObject::rotateAroundY(float angle, const std::vector<float> &rotationPoint)
{
    for (int i = 0; i < length; i++)
    {
        this->triangles->at(i).rotateAroundY(angle, rotationPoint);
    }
}

void TriangleObject::rotateAroundZ(float angle, const std::vector<float> &rotationPoint)
{
    for (int i = 0; i < length; i++)
    {
        this->triangles->at(i).rotateAroundZ(angle, rotationPoint);
    }
}

void TriangleObject::project(Canvas &c)
{
    for (int i = 0; i < length; i++)
    {
        this->triangles->at(i).project(c); 
    }
}

int TriangleObject::size()
{
    return length;
}

void TriangleObject::scale(float k)
{
    for (int i = 0; i < length; i++)
    {
        this->triangles->at(i).scale(k); 
    }
}

void TriangleObject::translate(float x, float y, float z)
{
    for (int i = 0; i < length; i++)
    {
        this->triangles->at(i).translate(x, y, z);
    }
}
