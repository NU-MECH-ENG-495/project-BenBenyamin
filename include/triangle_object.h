#include <vector>
#include <string>
#include "triangle.h"


class TriangleObject
{
public:
    TriangleObject(const std::string &stlFileName);
    void rotateAroundX(float angle, const std::vector<float> &rotationPoint);

    int size();

private:
    std::vector<TriangleSurface> triangles;
};
