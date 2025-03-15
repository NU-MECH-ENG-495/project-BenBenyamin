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

    // Define the eight vertices of the cube
    std::vector<std::vector<float>> vertices = 
    {
        // Front face
        {200.0f, 200.0f, 300.0f}, // 0 - Bottom-left front
        {300.0f, 200.0f, 300.0f}, // 1 - Bottom-right front
        {300.0f, 300.0f, 300.0f}, // 2 - Top-right front
        {200.0f, 300.0f, 300.0f}, // 3 - Top-left front
        
        // Back face
        {200.0f, 200.0f, 400.0f}, // 4 - Bottom-left back
        {300.0f, 200.0f, 400.0f}, // 5 - Bottom-right back
        {300.0f, 300.0f, 400.0f}, // 6 - Top-right back
        {200.0f, 300.0f, 400.0f}  // 7 - Top-left back
    };
    
    // Define colors for each face
    std::vector<float> red = {1.0f, 0.0f, 0.0f};    // Front face
    std::vector<float> blue = {0.0f, 0.0f, 1.0f};   // Right face
    std::vector<float> green = {0.0f, 1.0f, 0.0f};  // Left face
    std::vector<float> yellow = {1.0f, 1.0f, 0.0f}; // Back face
    std::vector<float> white = {1.0f, 1.0f, 1.0f};  // Top face
    std::vector<float> gray = {0.5f, 0.5f, 0.5f};   // Bottom face
    
    // Define the cube faces using two triangles per face
    std::vector<TriangleSurface> faces = {
        // Front face (red)
        {vertices[0], vertices[1], vertices[2], red}, 
        // {vertices[0], vertices[2], vertices[3], red}, 

        // // Right face (blue)
        // {vertices[1], vertices[5], vertices[6], blue}, 
        // {vertices[1], vertices[6], vertices[2], blue}, 

        // Back face (yellow)
        {vertices[5], vertices[4], vertices[7], yellow}, 
        // {vertices[5], vertices[7], vertices[6], yellow}, 

        // // Left face (green)
        // {vertices[4], vertices[0], vertices[3], green}, 
        // {vertices[4], vertices[3], vertices[7], green}, 

        // // Top face (white)
        // {vertices[3], vertices[2], vertices[6], white}, 
        // {vertices[3], vertices[6], vertices[7], white}, 

        // // Bottom face (gray)
        // {vertices[0], vertices[1], vertices[5], gray}, 
        // {vertices[0], vertices[5], vertices[4], gray}  
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
            face.rotateAroundY(rotationAngle, rotationCenter); // Rotate around Y-axis at cube center
        }

        std::string filename = "../output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}
