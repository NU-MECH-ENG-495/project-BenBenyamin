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
    float scaleFactor = 1.0f;
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    std::vector<std::vector<float>> vertices = {
        {centerX - scaleFactor, centerY - scaleFactor, -scaleFactor}, // A
        {centerX + scaleFactor, centerY - scaleFactor, -scaleFactor}, // B
        {centerX + scaleFactor, centerY + scaleFactor, -scaleFactor}, // C
        {centerX - scaleFactor, centerY + scaleFactor, -scaleFactor}, // D
        {centerX - scaleFactor, centerY - scaleFactor, scaleFactor},  // E
        {centerX + scaleFactor, centerY - scaleFactor, scaleFactor},  // F
        {centerX + scaleFactor, centerY + scaleFactor, scaleFactor},  // G
        {centerX - scaleFactor, centerY + scaleFactor, scaleFactor}   // H
    };

    // Define cube faces using triangles
    std::vector<std::vector<float>> colors = {
        {1.0f, 0.0f, 0.0f},  // Red
        {0.0f, 1.0f, 0.0f},  // Green
        {0.0f, 0.0f, 1.0f},  // Blue
        {1.0f, 1.0f, 0.0f},  // Yellow
        {1.0f, 0.0f, 1.0f},  // Magenta
        {0.0f, 1.0f, 1.0f}   // Cyan
    };

    std::vector<TriangleSurface> faces = {
        {vertices[0], vertices[1], vertices[2], colors[0]}, // Front face
        {vertices[0], vertices[2], vertices[3], colors[0]},
        {vertices[1], vertices[5], vertices[6], colors[1]}, // Right face
        {vertices[1], vertices[6], vertices[2], colors[1]},
        {vertices[5], vertices[4], vertices[7], colors[2]}, // Back face
        {vertices[5], vertices[7], vertices[6], colors[2]},
        {vertices[4], vertices[0], vertices[3], colors[3]}, // Left face
        {vertices[4], vertices[3], vertices[7], colors[3]},
        {vertices[3], vertices[2], vertices[6], colors[4]}, // Top face
        {vertices[3], vertices[6], vertices[7], colors[4]},
        {vertices[4], vertices[5], vertices[1], colors[5]}, // Bottom face
        {vertices[4], vertices[1], vertices[0], colors[5]}
    };

    // Initial camera normal facing directly along the Z-axis
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    int numFrames = 2;
    float rotationAngle = 360.0 / numFrames;

    for (int frame = 0; frame < numFrames; ++frame)
    {
        canvas.clear();

        for (auto &face : faces)
        {
            face.project(canvas);
            face.rotateAroundX(rotationAngle);
        }

        std::string filename = "output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}