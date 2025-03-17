#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include "canvas.h"
#include "triangle.h"
#include "stl.cpp"
#include "triangle_object.h"


#ifndef UNIT_TEST
int main()
{
    int width = 1000, height = 1000;
    Canvas canvas(height, width);
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    std::string filename = "/home/ben/Documents/Courses/Winter-2025/CPP/Project/example/ASCII.stl";
    TriangleObject triangleObject(filename); // Create TriangleObject and load the STL file
    std::cout << "Loaded " << triangleObject.size() << " triangles from " << filename << std::endl;

    std::vector<float> rotationCenter = {500.0f, 500.0f, 350.0f};

    // orient
    canvas.clear();
    triangleObject.scale(4.5);
    triangleObject.rotateAroundY(-90, rotationCenter);
    triangleObject.translate(-200, 0, 0);
    triangleObject.rotateAroundY(-15, rotationCenter);

    for (int i = 0; i < 3; i++)
    {
        triangleObject.project(canvas);
        triangleObject.rotateAroundX(6, rotationCenter);

        std::string outFileName = "../output/MODEL_" + std::to_string(i) + ".ppm";
        canvas.writePPM(outFileName);
        canvas.clear();
    }

    return 0;
}
#endif