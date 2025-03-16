#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include <omp.h>
#include "canvas.h"
#include "triangle.h"
#include "stl.h"
#include "triangle_object.h"

int main()
{
    int width = 1000, height = 1000;
    Canvas canvas(height, width);
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    std::string filename = "/home/ben/Documents/Courses/Winter-2025/CPP/Project/example/cube.stl";
    // std::vector<TriangleSurface> triangles = readSTL(filename);

    TriangleObject model (filename);

    std::cout << "Loaded " << model.size() << " triangles from " << filename << std::endl;

    std::vector<float> rotationCenter = {500.0f, 500.0f, 350.0f}; 

    // orient
    // canvas.clear();
    // for (auto &triangle : triangles) 
    // {
    //     triangle.scale(4.5);
    //     triangle.rotateAroundY(-90,rotationCenter);
    //     triangle.translate(-200,0,0);
    //     // triangle.rotateAroundZ(-90,rotationCenter);
    //     triangle.rotateAroundY(-15,rotationCenter);

    // }

    model.scale(2);
    model.translate(100,0,0);
    
    model.rotateAroundX(10,rotationCenter);
    model.rotateAroundY(10,rotationCenter);
    model.rotateAroundZ(10,rotationCenter);
    model.project(canvas);

    std::string outFileName = "../output/MODEL_OMP.ppm";
    canvas.writePPM(outFileName);

    // for (int i =0 ;i < 360/6; i ++)
    // {

    //     for (auto &triangle : triangles)
    //     {
    //         triangle.project(canvas);
    //         triangle.rotateAroundX(6,rotationCenter);
    //     }
    //     std::string outFileName = "../output/MODEL_" + std::to_string(i) + ".ppm";
    //     canvas.writePPM(outFileName);
    //     canvas.clear();
    
    // }
    return 0;
}