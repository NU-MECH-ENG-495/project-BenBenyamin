#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "Canvas.h"

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
    void translate(float x , float y , float z);

private:
    std::vector<float> A; // First point of the triangle
    std::vector<float> B; // Second point of the triangle
    std::vector<float> C; // Third point of the triangle
    std::vector<float> color;

#ifdef UNIT_TEST
public:
    // Make these private members accessible only for testing
    const std::vector<float>& getA() const { return A; }
    const std::vector<float>& getB() const { return B; }
    const std::vector<float>& getC() const { return C; }
    const std::vector<float>& getColor() const { return color; }
#endif
};

#endif // TRIANGLE_H
