#ifndef STL_H
#define STL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "triangle.h"
#include "canvas.h"

// Function to generate a random color
std::vector<float> getRandomColor();

// Function to read an STL file and return a vector of TriangleSurface objects
std::vector<TriangleSurface> readSTL(const std::string &filename);

#endif // YOUR_FILE_H
