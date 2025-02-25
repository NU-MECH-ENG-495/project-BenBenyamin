#include <iostream>
#include "canvas.h"
#include "triangle.h"  // Assuming this header contains TriangleSurface definition

int main()
{
    // Create a Canvas object with a height of 1000 and a width of 1000
    int width = 1000, height = 1000;
    Canvas canvas(width, height);

    // Define the vertices of the triangle (in 3D space)
    std::vector<float> A = {100, 100, 0};  // Vertex A
    std::vector<float> B = {200, 100, 0};  // Vertex B
    std::vector<float> C = {150, 200, 0};  // Vertex C

    // Create a TriangleSurface object with the given vertices and a red color
    TriangleSurface triangle(A, B, C, {1.0f, 0.0f, 0.0f});  // Red color for the triangle

    // Set the camera normal to (0, 0, 1) (pointing along the z-axis)
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};

    canvas.setCameraNormal(cameraNormal);

    // Project the triangle onto the canvas
    triangle.project(canvas);

    // Write the canvas to a PPM file
    canvas.writePPM("output.ppm");

    return 0;
};
