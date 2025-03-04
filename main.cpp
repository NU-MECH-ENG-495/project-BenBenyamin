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

    // Define the four vertices of the tetrahedron
    float scaleFactor = 200.0f; // Scale factor for tetrahedron size
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    std::vector<float> A = {centerX, centerY - scaleFactor, 1.0f}; // Top vertex
    std::vector<float> B = {centerX - scaleFactor, centerY + scaleFactor, 1.0f}; // Bottom left vertex
    std::vector<float> C = {centerX + scaleFactor, centerY + scaleFactor, 1.0f}; // Bottom right vertex
    std::vector<float> D = {centerX, centerY, 1.0f + scaleFactor}; // Front vertex (raised along Z-axis)

    // Define the four faces of the tetrahedron
    std::vector<float> red = {1.0f, 0.0f, 0.0f};    // Red
    std::vector<float> green = {0.0f, 1.0f, 0.0f};  // Green
    std::vector<float> blue = {0.0f, 0.0f, 1.0f};   // Blue
    std::vector<float> yellow = {1.0f, 1.0f, 0.0f}; // Yellow

    // Create the four triangles (faces) of the tetrahedron
    TriangleSurface face1(A, B, C, red);    // Base triangle
    TriangleSurface face2(A, B, D, green);  // Front-left triangle
    TriangleSurface face3(A, C, D, blue);   // Front-right triangle
    TriangleSurface face4(B, C, D, yellow); // Back triangle

    // Initial camera normal facing directly along the Z-axis
    std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
    canvas.setCameraNormal(cameraNormal);

    int numFrames = 5;                     // Number of frames for the animation (one per rotation)
    float rotationAngle = 360.0 / numFrames; // Angle for each rotation

    // Generate frames for the animation
    for (int frame = 0; frame < numFrames; ++frame)
    {
        // Clear the canvas for the new frame
        canvas.clear();

        // Project and render all four faces of the tetrahedron
        face1.project(canvas);
        face2.project(canvas);
        face3.project(canvas);
        face4.project(canvas);

        // Rotate the tetrahedron around the X-axis
        face1.rotateAroundX(rotationAngle);
        face2.rotateAroundX(rotationAngle);
        face3.rotateAroundX(rotationAngle);
        face4.rotateAroundX(rotationAngle);

        // Save the current frame to a .ppm file
        std::string filename = "output/frame_" + std::to_string(frame) + ".ppm";
        canvas.writePPM(filename);
    }

    std::cout << "Animation frames saved in the 'output' folder." << std::endl;
    return 0;
}