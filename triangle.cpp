#include <vector>
#include <numeric>
#include "triangle.h"
#include "canvas.h"

TriangleSurface::TriangleSurface(const std::vector<float> &a, const std::vector<float> &b, const std::vector<float> &c, const std::vector<float> &color) 
    : A{a}, B{b}, C{c}, color{color} {}

void TriangleSurface::project(Canvas &c)
{
    auto normal = c.getCameraNormal();
    std::vector<float> projectedA = projectPointToPlane(A, normal);
    std::vector<float> projectedB = projectPointToPlane(B, normal);
    std::vector<float> projectedC = projectPointToPlane(C, normal);

    // TODO: Make these loops scope smaller

    for (int i = 0; i < c.getWidth(); ++i)
    {
        for (int j = 0; j < c.getHeight(); ++j)
        {
            std::vector<float> point = {static_cast<float>(i), static_cast<float>(j)};

            if (isInside(point, projectedA, projectedB, projectedC))
            {
                c.putPixel(i, j, color);
            }
        }
    }
}

bool TriangleSurface::isInside(std::vector<float> &point, const std::vector<float>& projectedA, const std::vector<float>& projectedB, const std::vector<float>& projectedC) const
{
    // Calculate the vectors from the reference point A to B, C, and the point P
    std::vector<float> AB = {projectedB[0] - projectedA[0], projectedB[1] - projectedA[1]};
    std::vector<float> AC = {projectedC[0] - projectedA[0], projectedC[1] - projectedA[1]};
    std::vector<float> AP = {point[0] - projectedA[0], point[1] - projectedA[1]};

    // Calculate the determinant (denom) for the matrix M
    float det = AB[0] * AC[1] - AB[1] * AC[0];

    if (det == 0)
    {
        return false; // Points are collinear; not inside the triangle
    }

    // Calculate (u, v) using Cramer's rule
    float u = (AC[1] * AP[0] - AC[0] * AP[1]) / det;
    float v = (AB[0] * AP[1] - AB[1] * AP[0]) / det;

    // The point is inside the triangle if 0 <= u, v <= 1, and u + v <= 1
    return (u >= 0 && v >= 0 && u + v <= 1);
}

std::vector<float> TriangleSurface::projectPointToPlane(const std::vector<float> &point, const std::vector<float> &normal) const
{
    std::vector<float> projection = point;
    float dotProduct = point[0] * normal[0] + point[1] * normal[1] + point[2] * normal[2];
    projection[0] -= dotProduct * normal[0];
    projection[1] -= dotProduct * normal[1];
    projection[2] -= dotProduct * normal[2];
    return projection;
}