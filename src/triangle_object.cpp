#include "triangle_object.h"
#include "stl.h"
#include "canvas.h"

TriangleObject::TriangleObject(const std::string &stlFileName)
{
    this->triangles = readSTL(stlFileName);
}

void TriangleObject::rotateAroundX(float angle, const std::vector<float> &rotationPoint)
{
    for (int i =0; i < this->triangles.size(); i++)
    {
        auto& triangle = triangles[i]; 
        triangle.rotateAroundX(angle,rotationPoint);
    }
}

void TriangleObject::project(Canvas &c)
{
    for (int i =0; i < this->triangles.size(); i++)
    {
        auto& triangle = triangles[i]; 
        triangle.project(c);
    }
}

int TriangleObject::size()
{
    return this->triangles.size();
}


void TriangleObject::scale(float k)
{
    for (int i =0; i < this->triangles.size(); i++)
    {
        auto& triangle = triangles[i]; 
        triangle.scale(k);
    }
}

void TriangleObject::translate(float x , float y , float z)
{
    for (int i =0; i < this->triangles.size(); i++)
    {
        auto& triangle = triangles[i]; 
        triangle.translate(x,y,z);
    }
}