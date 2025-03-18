#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

#include "Canvas.h"
#include "linalg.h"
/**
 * @file canvas.cpp
 * @brief This file contains the implementation of the Canvas class, which represents a 2D canvas
 *        for rendering and storing pixel data with depth information.
 * 
 * The Canvas class provides functionality to manipulate pixels, clear the canvas, write the canvas
 * content to a PPM file, and manage camera-related properties such as the camera normal and orthonormal
 * basis vectors. It also includes methods for handling depth-based pixel placement and camera orientation.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */
/**
 * 
 * @brief Constructs a Canvas object with the specified height and width.
 * 
 * @param h The height of the canvas.
 * @param w The width of the canvas.
 */
Canvas::Canvas(int h, int w) : height(h), width(w), pixels(h, std::vector<std::vector<float>>(w, std::vector<float>(3, 0.0))), depth(h, std::vector<float>(w, 0.0f)) {};

/**
 * @brief Places a pixel with the specified color and depth at the given coordinates.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param depth The depth value of the pixel.
 * @param color The color of the pixel as a vector of 3 floats (RGB).
 */
void Canvas::putPixel(int x, int y, float depth, std::vector<float> &color)
{
    if (x >= 0 && x < height && y >= 0 && y < width && color.size() == 3)
    {
        if ((depth != 0 && this->depth[x][y] > depth )|| this->depth[x][y] == 0.0f)
        {
            this->pixels[x][y] = color;
            this->depth[x][y] = depth;  
        }
    }
}

/**
 * @brief Clears the canvas by resetting all pixels to black and depth values to zero.
 */
void Canvas::clear()
{
    std::vector<float> defaultColor = {0.0f, 0.0f, 0.0f};

    for (int i = 0; i < height; ++i)
    {
        std::fill(pixels[i].begin(), pixels[i].end(), defaultColor);
        std::fill(depth[i].begin(), depth[i].end(), 0);
    }
}

/**
 * @brief Returns the width of the canvas.
 * 
 * @return The width of the canvas.
 */
int Canvas::getWidth() const { return width; }

/**
 * @brief Returns the height of the canvas.
 * 
 * @return The height of the canvas.
 */
int Canvas::getHeight() const { return height; }

/**
 * @brief Writes the canvas content to a PPM file.
 * 
 * @param filename The name of the file to write the PPM data to.
 */
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

/**
 * @brief Sets the camera normal vector and calculates the orthonormal basis.
 * 
 * @param normal The normal vector to set as the camera normal.
 * @throws std::invalid_argument If the normal vector is invalid (not 3D or zero vector).
 */
void Canvas::setCameraNormal(std::vector<float> &normal)
{
    // Check if the normal vector has 3 elements (for 3D space)
    if (normal.size() != 3)
    {
        throw std::invalid_argument("Normal vector must have 3 elements.");
    }

    // Calculate the magnitude (length) of the vector
    float magnitude = 0.0f;
    for (float val : normal)
    {
        magnitude += val * val;
    }

    magnitude = std::sqrt(magnitude);

    // Avoid division by zero (check if the vector is not a zero vector)
    if (magnitude == 0.0f)
    {
        throw std::invalid_argument("Normal vector cannot be a zero vector.");
    }

    // Normalize the normal vector by dividing each component by the magnitude
    for (float &val : normal)
    {
        val /= magnitude;
    }

    this->cameraNormal = normal;
    // Call calculateOrthonormals to get the orthonormal basis
    std::vector<std::vector<float>> orthonormals = calculateOrthonormals(normal);

    // Save the result to cameraOrthonormal1 and cameraOrthonormal2
    this->cameraOrthonormal1 = orthonormals[0]; 
    this->cameraOrthonormal2 = orthonormals[1];

    this->clear(); // clear the canvas because the camera position was changed.
}

/**
 * @brief Returns the camera normal vector.
 * 
 * @return The camera normal vector.
 */
std::vector<float> Canvas::getCameraNormal() const {return this->cameraNormal;}

/**
 * @brief Returns the camera axis as a set of orthonormal vectors.
 * 
 * @return A vector containing the camera normal and its orthonormal basis vectors.
 */
std::vector<std::vector<float>> Canvas::getCameraAxis() const {return {this->cameraNormal,this->cameraOrthonormal1,this->cameraOrthonormal2};}