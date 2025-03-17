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

    std::string filename = "/home/ben/Documents/Courses/Winter-2025/CPP/Project/example/ASCII.stl";
    auto triangles = std::make_shared<std::vector<TriangleSurface>>();
    readSTL(filename, triangles);
    std::cout << "Loaded " << triangles->size() << " triangles from " << filename << std::endl;

    std::vector<float> rotationCenter = {500.0f, 500.0f, 350.0f};

    // orient
    canvas.clear();
    for (auto &triangle : *triangles) // Dereference to access the vector
    {
        triangle.scale(4.5);
        triangle.rotateAroundY(-90, rotationCenter);
        triangle.translate(-200, 0, 0);
        // triangle.rotateAroundZ(-90, rotationCenter); // Uncomment if needed
        triangle.rotateAroundY(-15, rotationCenter);
    }

    for (int i = 0; i < 1; i++)
    {
        for (auto &triangle : *triangles) // Dereference to access the vector
        {
            triangle.project(canvas);
            triangle.rotateAroundX(6, rotationCenter);
        }

        std::string outFileName = "../output/MODEL_" + std::to_string(i) + ".ppm";
        canvas.writePPM(outFileName);
        canvas.clear();
    }

    return 0;
}
