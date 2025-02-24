#include <iostream>
#include "canvas.h"
#include "sphere.h"

int main()
{
    // Create a Canvas object with a height of 50 and a width of 50
    int width = 1000, height = 1000;
    Canvas canvas(height, width);

    // Create a Sphere object at (x=25, y=25) with a radius of 20 and red color
    Sphere sphere(2, 50, 30, 0.10, {1.0, 0.0, 0.0}); // Red color sphere

    // Project the sphere onto the canvas (this will color the pixels where the sphere is)
    sphere.project(canvas);

    // Write the canvas to a PPM file
    canvas.writePPM("output.ppm");

    return 0;
};