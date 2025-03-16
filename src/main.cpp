#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include "canvas.h"
#include "triangle.h"
#include "stl.cpp"

int main()
{
    int width = 1000, height = 1000;
    Canvas canvas(height, width);
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    std::string filename = "/home/ben/Documents/Courses/Winter-2025/CPP/Project/example/eiffel.stl";
    std::vector<TriangleSurface> triangles = readSTL(filename);
    std::cout << "Loaded " << triangles.size() << " triangles from " << filename << std::endl;

    std::vector<float> rotationCenter = {500.0f, 500.0f, 350.0f}; 

    // orient
    canvas.clear();
    for (auto &triangle : triangles) 
    {
        triangle.scale(7);
        triangle.translate(500,500,0);
        triangle.rotateAroundX(90,rotationCenter);
        triangle.rotateAroundZ(-90,rotationCenter);
        // triangle.rotateAroundX(-15,rotationCenter);

    }

    for (int i =0 ;i < 360/15; i ++)
    {

        for (auto &triangle : triangles)
        {
            triangle.project(canvas);
            triangle.rotateAroundX(15,rotationCenter);
        }
        std::string outFileName = "../output/cube_" + std::to_string(i) + ".ppm";
        canvas.writePPM(outFileName);
        canvas.clear();
    
    }
    return 0;
}