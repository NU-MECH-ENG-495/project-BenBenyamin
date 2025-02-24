#include <algorithm>
#include <cmath>
#include <vector>
#include "canvas.h"
#include "sphere.h"

void Sphere::project(Canvas &c)
{
    double radiusSquared = std::pow(radius, 2);

    double scaledRadius = radius / z;

    // Calculate bounding box limits using the scaled radius
    int xStart = std::max(x - static_cast<int>(scaledRadius), 0);
    int xEnd = std::min(x + static_cast<int>(scaledRadius), c.getWidth());
    int yStart = std::max(y - static_cast<int>(scaledRadius), 0);
    int yEnd = std::min(y + static_cast<int>(scaledRadius), c.getHeight());

    // Loop over the bounding box of the sphere on the canvas
    for (int x_ = xStart; x_ <= xEnd; ++x_)
    {
        for (int y_ = yStart; y_ <= yEnd; ++y_)
        {
            // Check if the point is within the sphere's radius using the circle equation
            double dx = x - x_;
            double dy = y - y_;
            if (dx * dx + dy * dy <= std::pow(scaledRadius, 2))
            {
                // Set the pixel color on the canvas
                c.putPixel(x_, y_, color);
            }
        }
    }
};