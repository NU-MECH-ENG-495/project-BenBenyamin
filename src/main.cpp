#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include "canvas.h"
#include "triangle.h"

int main()
{
    int width = 1000, height = 1000;
    Canvas canvas(height, width);

    // Define the four vertices of the square
    float scaleFactor = 10.0f; // Adjust the size of the square
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    std::vector<std::vector<float>> vertices = 
    {
        {200.0f, 200.0f, 300.0f},     // Bottom-left
        {300.0f, 200.0f, 300.0f},   // Bottom-right
        {300.0f, 300.0f, 300.0f},    // Top-right
        {200.0f, 300.0f, 300.0f},
        
    };

    // Define the color of the square
    std::vector<float> color = {1.0f, 0.0f, 0.0f}; // Red

    // Define the square using two triangles
    std::vector<TriangleSurface> faces = {
        {vertices[0], vertices[1], vertices[2], color}, // First triangle
        {vertices[0], vertices[2], vertices[3], color}
    };

    // Initial camera normal facing directly along the Z-axis
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    int numFrames = 1;
    float rotationAngle = 360.0 / numFrames;

    for (int frame = 0; frame < numFrames; ++frame)
    {
        canvas.clear();

        for (auto &face : faces)
        {
            face.project(canvas);
            // face.rotateAroundX(rotationAngle);
        }

        std::string filename = "../output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}