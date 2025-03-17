/**
 * @file triangle_object.cpp
 * @brief This file contains the implementation of the TriangleObject class.
 * 
 * The TriangleObject class represents a collection of TriangleSurface objects, typically loaded from an STL file.
 * It provides methods for projecting all triangles onto a canvas, applying transformations (rotation, scaling, translation)
 * to all triangles, and querying the number of triangles in the object.
 * 
 * @author Your Name
 * @date October 2023
 */

 #include <omp.h> // OpenMP for parallel processing
 #include "triangle_object.h"
 #include "triangle.h"
 #include "canvas.h"
 #include "stl.h"
 
 /**
  * @brief Constructs a TriangleObject by loading triangle data from an STL file.
  * 
  * @param stlFileName The path to the STL file containing the triangle data.
  */
 TriangleObject::TriangleObject(const std::string &stlFileName)
 {
     triangles = std::make_shared<std::vector<TriangleSurface>>(); // Initialize the shared pointer for triangles
     readSTL(stlFileName, triangles); // Load triangle data from the STL file
 }
 
 /**
  * @brief Projects all triangles in the object onto the canvas.
  * 
  * This function iterates over all triangles and projects each one onto the canvas using the `project` method
  * of the TriangleSurface class.
  * 
  * @param c The canvas onto which the triangles are projected.
  */
 void TriangleObject::project(Canvas &c)
 {
     for (int i = 0; i < triangles->size(); ++i)
     {
         (*triangles)[i].project(c); // Project each triangle onto the canvas
     }
 }
 
 /**
  * @brief Rotates all triangles in the object around the X-axis by a given angle.
  * 
  * This function applies a rotation transformation to all triangles in parallel using OpenMP.
  * 
  * @param angle The angle of rotation in degrees.
  * @param rotationPoint The point around which the triangles are rotated.
  */
 void TriangleObject::rotateAroundX(float angle, const std::vector<float> &rotationPoint)
 {
     #pragma omp parallel for // Parallelize the loop using OpenMP
     for (int i = 0; i < triangles->size(); ++i)
     {
         (*triangles)[i].rotateAroundX(angle, rotationPoint); // Rotate each triangle around the X-axis
     }
 }
 
 /**
  * @brief Rotates all triangles in the object around the Y-axis by a given angle.
  * 
  * This function applies a rotation transformation to all triangles in parallel using OpenMP.
  * 
  * @param angle The angle of rotation in degrees.
  * @param rotationPoint The point around which the triangles are rotated.
  */
 void TriangleObject::rotateAroundY(float angle, const std::vector<float> &rotationPoint)
 {
     #pragma omp parallel for // Parallelize the loop using OpenMP
     for (int i = 0; i < triangles->size(); ++i)
     {
         (*triangles)[i].rotateAroundY(angle, rotationPoint); // Rotate each triangle around the Y-axis
     }
 }
 
 /**
  * @brief Rotates all triangles in the object around the Z-axis by a given angle.
  * 
  * This function applies a rotation transformation to all triangles in parallel using OpenMP.
  * 
  * @param angle The angle of rotation in degrees.
  * @param rotationPoint The point around which the triangles are rotated.
  */
 void TriangleObject::rotateAroundZ(float angle, const std::vector<float> &rotationPoint)
 {
     #pragma omp parallel for // Parallelize the loop using OpenMP
     for (int i = 0; i < triangles->size(); ++i)
     {
         (*triangles)[i].rotateAroundZ(angle, rotationPoint); // Rotate each triangle around the Z-axis
     }
 }
 
 /**
  * @brief Scales all triangles in the object by a given factor.
  * 
  * This function applies a scaling transformation to all triangles in parallel using OpenMP.
  * 
  * @param k The scaling factor.
  */
 void TriangleObject::scale(float k)
 {
     #pragma omp parallel for // Parallelize the loop using OpenMP
     for (int i = 0; i < triangles->size(); ++i)
     {
         (*triangles)[i].scale(k); // Scale each triangle
     }
 }
 
 /**
  * @brief Translates all triangles in the object by a given offset.
  * 
  * This function applies a translation transformation to all triangles in parallel using OpenMP.
  * 
  * @param x The offset in the X direction.
  * @param y The offset in the Y direction.
  * @param z The offset in the Z direction.
  */
 void TriangleObject::translate(float x, float y, float z)
 {
     #pragma omp parallel for // Parallelize the loop using OpenMP
     for (int i = 0; i < triangles->size(); ++i)
     {
         (*triangles)[i].translate(x, y, z); // Translate each triangle
     }
 }
 
 /**
  * @brief Returns the number of triangles in the object.
  * 
  * @return The number of triangles in the object.
  */
 int TriangleObject::size()
 {
     return static_cast<int>(triangles->size()); // Return the size of the triangles vector
 }