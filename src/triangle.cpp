/**
 * @file triangle.cpp
 * @brief This file contains the implementation of the TriangleSurface class.
 * 
 * The TriangleSurface class represents a 3D triangle surface defined by three vertices (A, B, C)
 * and a color. It provides methods for projecting the triangle onto a 2D canvas, checking if a point
 * lies inside the triangle, and applying transformations such as rotation, scaling, and translation.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */

 #include <vector>
 #include <numeric>
 #include <cmath>
 #include <iostream>
 #include "triangle.h"
 #include "canvas.h"
 #include "linalg.h"
 
 /**
  * @brief Constructs a TriangleSurface object with the given vertices and color.
  * 
  * @param a The first vertex of the triangle.
  * @param b The second vertex of the triangle.
  * @param c The third vertex of the triangle.
  * @param color The color of the triangle as a vector of three floats (RGB).
  */
 TriangleSurface::TriangleSurface(const std::vector<float> &a, const std::vector<float> &b, const std::vector<float> &c, const std::vector<float> &color)
     : A{a}, B{b}, C{c}, color{color} {}
 
 /**
  * @brief Projects the triangle onto the canvas and renders it.
  * 
  * This function projects the triangle's vertices onto the canvas using the camera's normal vector
  * and renders the triangle by iterating over the projected area. It uses the `isInside` function
  * to determine if a point lies inside the triangle and the `putPixel` method of the canvas to render it.
  * 
  * @param c The canvas onto which the triangle is projected.
  */
 void TriangleSurface::project(Canvas &c)
 {   
     auto cameraAxis = c.getCameraAxis();
     auto normal = cameraAxis[0];
 
     // Project the triangle's vertices onto the plane defined by the camera's normal vector
     std::vector<float> projectedA = projectPointToPlane(A, normal);
     std::vector<float> projectedB = projectPointToPlane(B, normal);
     std::vector<float> projectedC = projectPointToPlane(C, normal);
 
     // Calculate the extremes of the projected triangle for rendering
     auto extremes = calculateDotProductExtremes(projectedA, projectedB, projectedC, cameraAxis);
 
     // Iterate over the projected area and render the triangle
     for (int i = extremes.first.first; i < extremes.first.second; ++i)
     {
         for (int j = extremes.second.first; j <  extremes.second.second; ++j)
         {
             std::vector<float> point = {static_cast<float>(i), static_cast<float>(j)};
 
             // Check if the point is inside the triangle
             auto point3D = isInside(point, projectedA, projectedB, projectedC);
 
             if (!point3D.empty()) // If the point is inside the triangle, render it
             {
                 // Calculate the depth of the point
                 auto depth = static_cast<int>(dotProduct(point3D, normal));
 
                 // Render the pixel on the canvas
                 c.putPixel(i, j, depth, color);
             }
         }
     }
 }
 
 /**
  * @brief Checks if a 2D point lies inside the projected triangle.
  * 
  * This function uses barycentric coordinates to determine if a point lies inside the triangle
  * defined by the projected vertices A, B, and C.
  * 
  * @param point The 2D point to check.
  * @param projectedA The first projected vertex of the triangle.
  * @param projectedB The second projected vertex of the triangle.
  * @param projectedC The third projected vertex of the triangle.
  * @return A 3D vector representing the point's coordinates if it lies inside the triangle; otherwise, an empty vector.
  */
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
         std::vector<float> point3D = 
         {
             A[0] + u * (B[0] - A[0]) + v * (C[0] - A[0]),
             A[1] + u * (B[1] - A[1]) + v * (C[1] - A[1]),
             A[2] + u * (B[2] - A[2]) + v * (C[2] - A[2])
         };
 
         return point3D;
     }
 
     return {}; // Point is not inside the triangle
 }
 
 /**
  * @brief Projects a 3D point onto a plane defined by a normal vector.
  * 
  * @param point The 3D point to project.
  * @param normal The normal vector of the plane.
  * @return The projected 3D point.
  */
 std::vector<float> TriangleSurface::projectPointToPlane(
     const std::vector<float> &point,
     const std::vector<float> &normal) const
 {
     // Project the point onto the plane
     std::vector<float> projection = point;
     
     float dProd = dotProduct(point, normal);
     projection[0] -= dProd * normal[0];
     projection[1] -= dProd * normal[1];
     projection[2] -= dProd * normal[2];
 
     return projection;
 }
 
 /**
  * @brief Rotates the triangle around the X-axis by a given angle.
  * 
  * @param angle The angle of rotation in degrees.
  * @param rotationPoint The point around which the triangle is rotated.
  */
 void TriangleSurface::rotateAroundX(float angle, const std::vector<float> &rotationPoint)
 {
     // Convert angle from degrees to radians
     float rad = angle * M_PI / 180.0f;
     float cosA = cos(rad);
     float sinA = sin(rad);
 
     // Translate points to origin by subtracting the rotation point
     for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
     {
         point.get()[0] -= rotationPoint[0];
         point.get()[1] -= rotationPoint[1];
         point.get()[2] -= rotationPoint[2];
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
         point.get()[0] += rotationPoint[0];
         point.get()[1] += rotationPoint[1];
         point.get()[2] += rotationPoint[2];
     }
 }
 
 /**
  * @brief Rotates the triangle around the Y-axis by a given angle.
  * 
  * @param angle The angle of rotation in degrees.
  * @param rotationPoint The point around which the triangle is rotated.
  */
 void TriangleSurface::rotateAroundY(float angle, const std::vector<float> &rotationPoint)
 {
     // Convert angle from degrees to radians
     float rad = angle * M_PI / 180.0f;
     float cosA = cos(rad);
     float sinA = sin(rad);
 
     // Translate points to origin by subtracting the rotation point
     for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
     {
         point.get()[0] -= rotationPoint[0];
         point.get()[1] -= rotationPoint[1];
         point.get()[2] -= rotationPoint[2];
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
         point.get()[0] += rotationPoint[0];
         point.get()[1] += rotationPoint[1];
         point.get()[2] += rotationPoint[2];
     }
 }
 
 /**
  * @brief Rotates the triangle around the Z-axis by a given angle.
  * 
  * @param angle The angle of rotation in degrees.
  * @param rotationPoint The point around which the triangle is rotated.
  */
 void TriangleSurface::rotateAroundZ(float angle, const std::vector<float> &rotationPoint)
 {
     // Convert angle from degrees to radians
     float rad = angle * M_PI / 180.0f;
     float cosA = cos(rad);
     float sinA = sin(rad);
 
     // Translate points to origin by subtracting the rotation point
     for (auto &point : {std::ref(A), std::ref(B), std::ref(C)})
     {
         point.get()[0] -= rotationPoint[0];
         point.get()[1] -= rotationPoint[1];
         point.get()[2] -= rotationPoint[2];
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
         point.get()[0] += rotationPoint[0];
         point.get()[1] += rotationPoint[1];
         point.get()[2] += rotationPoint[2];
     }
 }
 
 /**
  * @brief Scales the triangle by a given factor.
  * 
  * @param k The scaling factor.
  */
 void TriangleSurface::scale(float k)
 {
     this->A[0] *= k;
     this->A[1] *= k;
     this->A[2] *= k;
 
     this->B[0] *= k;
     this->B[1] *= k;
     this->B[2] *= k;
 
     this->C[0] *= k;
     this->C[1] *= k;
     this->C[2] *= k;
 }
 
 /**
  * @brief Translates the triangle by a given offset.
  * 
  * @param x The offset in the X direction.
  * @param y The offset in the Y direction.
  * @param z The offset in the Z direction.
  */
 void TriangleSurface::translate(float x, float y, float z)
 {
     this->A[0] += x;
     this->A[1] += y;
     this->A[2] += z;
 
     this->B[0] += x;
     this->B[1] += y;
     this->B[2] += z;
 
     this->C[0] += x;
     this->C[1] += y;
     this->C[2] += z;
 }