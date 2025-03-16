#include <vector>
#include <string>
#include "triangle.h"


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
    std::vector<TriangleSurface> triangles;
};
