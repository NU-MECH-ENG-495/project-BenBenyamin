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

    // Triangle centered in the canvas
    float scaleFactor = 3.0f; // Scale factor for triangle size
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    // Center the triangle based on the canvas size
    std::vector<float> A = {centerX - 150 * scaleFactor, centerY - 100 * scaleFactor, 2};
    std::vector<float> B = {centerX - 150 * scaleFactor, centerY + 100 * scaleFactor, 2};
    std::vector<float> C = {centerX + 150 * scaleFactor, centerY, 1.5};

    // Create the triangle with fixed color
    std::vector<float> color = {1.0f, 0.0f, 0.0f}; // Red color
    TriangleSurface triangle(A, B, C, color);

    // Initial camera normal facing directly along the Z-axis
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    int numFrames = 1;                     // Number of frames for the animation (one per rotation)
    float rotationAngle = 360.0 / numFrames; // Angle for each rotation

    // Generate frames for the animation
    for (int frame = 0; frame < numFrames; ++frame)
    {
        // Clear the canvas for the new frame
        canvas.clear();

        // Project and render the triangle with the rotated camera normal
        triangle.project(canvas);

        // Rotate the triangle but keep the triangle's position fixed
        triangle.rotateAroundX(rotationAngle);

        // Save the current frame to a .ppm file
        std::string filename = "output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}