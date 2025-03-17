#ifndef TRIOBJ_H
#define TRIOBJ_H

#include <vector>
#include <string>
#include <memory>
//#include "triangle.h"

class TriangleSurface;
class Canvas;

class TriangleObject
{
public:
    TriangleObject(const std::string &stlFileName);
    
    void project(Canvas &c);
    
    void rotateAroundX(float angle, const std::vector<float> &rotationPoint);
    void rotateAroundY(float angle, const std::vector<float> &rotationPoint);
    void rotateAroundZ(float angle, const std::vector<float> &rotationPoint);

    void scale(float k);
    void translate(float x , float y , float z);

    int size();

private:

    std::shared_ptr<std::vector<TriangleSurface>> triangles;
    size_t length;
};

#endif
