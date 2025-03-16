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

    std::vector<float> rotationCenter = {250.0f, 250.0f, 350.0f}; 

    for (int i =0 ;i < 1; i ++)
    {
        canvas.clear();
        for (auto &triangle : triangles) 
        {
            triangle.rotateAroundX(15,rotationCenter);
            triangle.rotateAroundY(15,rotationCenter);
            triangle.project(canvas);
        }

        std::string outFileName = "../output/cube_" + std::to_string(i) + ".ppm";
        canvas.writePPM(outFileName);
    }
    return 0;
}