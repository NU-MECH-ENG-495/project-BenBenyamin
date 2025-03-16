#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "canvas.h"

class TriangleSurface
{

public:
    TriangleSurface(const std::vector<float> &a, const std::vector<float> &b, const std::vector<float> &c, const std::vector<float> &color);

    void project(Canvas &c);

    std::vector<float> isInside(std::vector<float> &point, const std::vector<float> &projectedA, const std::vector<float> &projectedB, const std::vector<float> &projectedC) const;

    std::vector<float> projectPointToPlane(const std::vector<float> &point, const std::vector<float> &normal) const;

    void rotateAroundX(float angle, const std::vector<float> &rotationPoint);
    void rotateAroundY(float angle, const std::vector<float> &rotationPoint);
    void rotateAroundZ(float angle, const std::vector<float> &rotationPoint);

    void scale(float k);

private:
    
    std::vector<float> A; // first point of the triangle
    std::vector<float> B; // second point of the triangle
    std::vector<float> C; // third point of the triangle
    std::vector<float> color;
};

#endif // TRIANGLE_H
