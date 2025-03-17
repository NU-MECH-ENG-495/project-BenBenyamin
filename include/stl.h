#ifndef STL_H
#define STL_H

#include <memory>
#include <vector>
#include "triangle.h"
#include "canvas.h"

// Function to generate a random color
std::vector<float> getRandomColor();

// Function to read an STL file and return a vector of TriangleSurface objects
void readSTL(const std::string &filename, std::shared_ptr<std::vector<TriangleSurface>> triangles);

#endif