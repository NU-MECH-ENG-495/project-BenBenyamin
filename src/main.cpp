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

    // Define the four vertices of the front face
    std::vector<std::vector<float>> vertices = 
    {
        // Front face
        {200.0f, 200.0f, 300.0f},     // Bottom-left (front)
        {300.0f, 200.0f, 300.0f},     // Bottom-right (front)
        {300.0f, 300.0f, 300.0f},     // Top-right (front)
        {200.0f, 300.0f, 300.0f},     // Top-left (front)
        
        // Right face
        {300.0f, 200.0f, 400.0f},     // Bottom-right (back)
        {300.0f, 300.0f, 400.0f}      // Top-right (back)
    };
    
    // Define colors
    std::vector<float> red = {1.0f, 0.0f, 0.0f};  // Front face color (red)
    std::vector<float> blue = {0.0f, 0.0f, 1.0f}; // Right face color (blue)
    
    // Define the cube faces using two triangles per face
    std::vector<TriangleSurface> faces = {
        // Front face (red)
        {vertices[0], vertices[1], vertices[2], red}, // First triangle
        {vertices[0], vertices[2], vertices[3], red}, // Second triangle
        
        // Right face (blue) - fixed to include correct points
        {vertices[1], vertices[4], vertices[5], blue}, // First triangle (right face)
        {vertices[1], vertices[2], vertices[5], blue}  // Second triangle (right face)
    };

    // Initial camera normal facing directly along the Z-axis
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    // Rotation setup
    int numFrames = 2;
    float rotationAngle = 360.0f / numFrames;

    // Cube center for rotation
    std::vector<float> rotationCenter = {250.0f, 250.0f, 350.0f}; // Approximate center of the cube

    for (int frame = 0; frame < numFrames; ++frame)
    {
        canvas.clear();

        for (auto &face : faces)
        {
            face.project(canvas);
            face.rotateAroundY(90.0, rotationCenter); // Rotate around Y-axis at cube center
        }

        std::string filename = "../output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}
