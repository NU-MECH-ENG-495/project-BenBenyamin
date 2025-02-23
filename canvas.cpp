#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "canvas.h"

Canvas::Canvas(int h, int w) : height(h), width(w), pixels(h, std::vector<std::vector<float>>(w, std::vector<float>(3, 0.0))) {}

void Canvas::putPixel(int x, int y, std::vector<float> &color)
{
    if (x >= 0 && x < height && y >= 0 && y < width && color.size() == 3)
    {
        this->pixels[x][y] = color;
    }
    else
    {
        throw std::invalid_argument("Invalid coordinates or color");
    }
}

int Canvas::getWidth() { return width; }
int Canvas::getHeight() { return height; }

void Canvas::writePPM(const std::string &filename)
{
    std::ofstream ppmFile(filename);

    if (!ppmFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Write the PPM header
    ppmFile << "P3\n";                         // P3 is the ASCII encoding for PPM
    ppmFile << width << " " << height << "\n"; // Canvas dimensions
    ppmFile << "255\n";                        // Max color value (255 for RGB)

    // Write the pixel data
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto pixel = pixels[i][j];

            // Convert pixel intensity (0.0 to 1.0) to (0 to 255)
            int r = static_cast<int>(pixel[0] * 255); // Red intensity
            int g = static_cast<int>(pixel[1] * 255); // Green intensity
            int b = static_cast<int>(pixel[2] * 255); // Blue intensity

            ppmFile << r << " " << g << " " << b << " ";
        }
        ppmFile << "\n";
    }

    // Close the file
    ppmFile.close();
    std::cout << "PPM file '" << filename << "' created successfully!" << std::endl;
}
