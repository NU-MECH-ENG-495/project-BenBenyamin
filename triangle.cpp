#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include "triangle.h"
#include "canvas.h"

TriangleSurface::TriangleSurface(const std::vector<float> &a, const std::vector<float> &b, const std::vector<float> &c, const std::vector<float> &color)
    : A{a}, B{b}, C{c}, color{color} {}

void TriangleSurface::project(Canvas &c)
{
    auto normal = c.getCameraNormal();

    std::vector<float> centroid = 
    {
        (A[0] + B[0] + C[0]) / 3.0f,
        (A[1] + B[1] + C[1]) / 3.0f,
        (A[2] + B[2] + C[2]) / 3.0f
    };

    std::vector<float> projectedA = projectPointToPlane(A, normal, centroid);
    std::vector<float> projectedB = projectPointToPlane(B, normal, centroid);
    std::vector<float> projectedC = projectPointToPlane(C, normal, centroid);

    // TODO: Make these loops scope smaller

    for (int i = 0; i < c.getWidth(); ++i)
    {
        for (int j = 0; j < c.getHeight(); ++j)
        {
            std::vector<float> point = {static_cast<float>(i), static_cast<float>(j)};

            auto point3D = isInside(point, projectedA, projectedB, projectedC);

            if (!point3D.empty()) // If the point is inside the triangle then render it
            {
                // Calculate the depth of the point
                float depth = point3D[0] * normal[0] + point[1] * point3D[1] + point[2] * point3D[2]; // the depth is the dot product 
                c.putPixel(i, j, depth, color);
            }
        }
    }
}

std::vector<float> TriangleSurface::isInside(
    std::vector<float> &point,
    const std::vector<float> &projectedA,
    const std::vector<float> &projectedB,
    const std::vector<float> &projectedC) const
{
    // Calculate the vectors from the reference point A to B, C, and the point P
    std::vector<float> AB = {projectedB[0] - projectedA[0], projectedB[1] - projectedA[1]};
    std::vector<float> AC = {projectedC[0] - projectedA[0], projectedC[1] - projectedA[1]};
    std::vector<float> AP = {point[0] - projectedA[0], point[1] - projectedA[1]};

    // Calculate the determinant (denom) for the matrix M
    float det = AB[0] * AC[1] - AB[1] * AC[0];

    if (det == 0)
    {
        return {}; // Points are collinear; not inside the triangle
    }

    // Calculate (u, v) using Cramer's rule
    float u = (AC[1] * AP[0] - AC[0] * AP[1]) / det;
    float v = (AB[0] * AP[1] - AB[1] * AP[0]) / det;

    // The point is inside the triangle if 0 <= u, v <= 1, and u + v <= 1
    if (u >= 0 && v >= 0 && u + v <= 1)
    {
        // Calculate the 3D coordinates of the point inside the triangle
        std::vector<float> point3D = {
            projectedA[0] + u * (projectedB[0] - projectedA[0]) + v * (projectedC[0] - projectedA[0]),
            projectedA[1] + u * (projectedB[1] - projectedA[1]) + v * (projectedC[1] - projectedA[1]),
            projectedA[2] + u * (projectedB[2] - projectedA[2]) + v * (projectedC[2] - projectedA[2])
        };
        return point3D;
    }

    return {}; // Point is not inside the triangle
}

std::vector<float> TriangleSurface::projectPointToPlane(
    const std::vector<float> &point,
    const std::vector<float> &normal,
    const std::vector<float> &center) const
{
    // Project the point onto the plane
    std::vector<float> projection = point;
    float dotProduct = point[0] * normal[0] + point[1] * normal[1] + point[2] * normal[2];
    projection[0] -= dotProduct * normal[0];
    projection[1] -= dotProduct * normal[1];
    projection[2] -= dotProduct * normal[2];

    // Scale the projection relative to the center
    float scale = 1.0f / dotProduct; // Perspective scaling factor per the dot product
    projection[0] = center[0] + (projection[0] - center[0]) * scale;
    projection[1] = center[1] + (projection[1] - center[1]) * scale;
    projection[2] = center[2] + (projection[2] - center[2]) * scale;

    return projection;
}

void TriangleSurface::rotateAroundX(float angle)
{
    // Convert angle from degrees to radians
    float rad = angle * M_PI / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // Compute centroid of the triangle
    float centerX = (A[0] + B[0] + C[0]) / 3.0f;
    float centerY = (A[1] + B[1] + C[1]) / 3.0f;
    float centerZ = (A[2] + B[2] + C[2]) / 3.0f;

    // Translate points to origin by subtracting the centroid
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        point.get()[0] -= centerX;
        point.get()[1] -= centerY;
        point.get()[2] -= centerZ;
    }

    // Rotate each vector around the X-axis
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        float newY = point.get()[1] * cosA - point.get()[2] * sinA;
        float newZ = point.get()[1] * sinA + point.get()[2] * cosA;
        point.get()[1] = newY;
        point.get()[2] = newZ;
    }

    // Translate points back to original position
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        point.get()[0] += centerX;
        point.get()[1] += centerY;
        point.get()[2] += centerZ;
    }
}

void TriangleSurface::rotateAroundY(float angle)
{
    // Convert angle from degrees to radians
    float rad = angle * M_PI / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // Compute centroid of the triangle
    float centerX = (A[0] + B[0] + C[0]) / 3.0f;
    float centerY = (A[1] + B[1] + C[1]) / 3.0f;
    float centerZ = (A[2] + B[2] + C[2]) / 3.0f;

    // Translate points to origin by subtracting the centroid
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        point.get()[0] -= centerX;
        point.get()[1] -= centerY;
        point.get()[2] -= centerZ;
    }

    // Rotate each vector around the Y-axis
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        float newX = point.get()[0] * cosA + point.get()[2] * sinA;
        float newZ = -point.get()[0] * sinA + point.get()[2] * cosA;
        point.get()[0] = newX;
        point.get()[2] = newZ;
    }

    // Translate points back to original position
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        point.get()[0] += centerX;
        point.get()[1] += centerY;
        point.get()[2] += centerZ;
    }
}

void TriangleSurface::rotateAroundZ(float angle)
{
    // Convert angle from degrees to radians
    float rad = angle * M_PI / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // Compute centroid of the triangle
    float centerX = (A[0] + B[0] + C[0]) / 3.0f;
    float centerY = (A[1] + B[1] + C[1]) / 3.0f;
    float centerZ = (A[2] + B[2] + C[2]) / 3.0f;

    // Translate points to origin by subtracting the centroid
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        point.get()[0] -= centerX;
        point.get()[1] -= centerY;
        point.get()[2] -= centerZ;
    }

    // Rotate each vector around the Z-axis
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        float newX = point.get()[0] * cosA - point.get()[1] * sinA;
        float newY = point.get()[0] * sinA + point.get()[1] * cosA;
        point.get()[0] = newX;
        point.get()[1] = newY;
    }

    // Translate points back to original position
    for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
    {
        point.get()[0] += centerX;
        point.get()[1] += centerY;
        point.get()[2] += centerZ;
    }
}