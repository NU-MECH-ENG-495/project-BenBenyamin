#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include "canvas.h"
#include "triangle.h"

void rotateCameraNormal(std::vector<float> &normal, float angle)
{
    // Rotate the camera normal around the X-axis in 3D space
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    float y = normal[1] * cosAngle - normal[2] * sinAngle;
    float z = normal[1] * sinAngle + normal[2] * cosAngle;
    normal[1] = y;
    normal[2] = z;
}


int main()
{
    int width = 1000, height = 1000;
    Canvas canvas(height, width);

    // Triangle centered in the canvas
    float scaleFactor = 3.0f;  // Scale factor for triangle size
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    
    // Center the triangle based on the canvas size
    std::vector<float> A = {centerX - 150 * scaleFactor, centerY - 100 * scaleFactor, 0};
    std::vector<float> B = {centerX - 150 * scaleFactor, centerY + 100 * scaleFactor, 0};
    std::vector<float> C = {centerX + 150 * scaleFactor, centerY, 0};

    // Create the triangle with fixed color
    std::vector<float> color = {1.0f, 0.0f, 0.0f}; // Red color
    TriangleSurface triangle(A, B, C, color);

    // Initial camera normal facing directly along the Z-axis
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    int numFrames = 36;  // Number of frames for the animation (one per rotation)
    float rotationAngle = -2 * M_PI / numFrames;  // Angle for each rotation

    // Generate frames for the animation
    for (int frame = 0; frame < numFrames; ++frame)
    {
        // Rotate the camera normal but keep the triangle's position fixed
        rotateCameraNormal(cameraNormal, rotationAngle);
        canvas.setCameraNormal(cameraNormal);

        // Clear the canvas for the new frame
        canvas.clear();

        // Project and render the triangle with the rotated camera normal
        triangle.project(canvas);

        // Save the current frame to a .ppm file
        std::string filename = "output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}