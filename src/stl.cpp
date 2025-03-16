#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "triangle.h"
#include "canvas.h"

// Function to generate a random color
std::vector<float> getRandomColor() {
    return {static_cast<float>(rand()) / RAND_MAX, 
            static_cast<float>(rand()) / RAND_MAX, 
            static_cast<float>(rand()) / RAND_MAX};
}

std::vector<TriangleSurface> readSTL(const std::string &filename)
{
    srand(0); // set the seed
    std::vector<TriangleSurface> triangles;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open STL file " << filename << std::endl;
        return triangles;
    }

    std::string line;
    std::vector<float> A(3), B(3), C(3);
    std::vector<float> color = {0.0f, 1.0f, 1.0f}; // Default white color

    int faceCounter = 0; // Counter to track face pairs

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "vertex")
        {
            if (!(iss >> A[0] >> A[1] >> A[2]))
                continue;

            std::getline(file, line);
            std::istringstream issB(line);
            issB >> keyword >> B[0] >> B[1] >> B[2];

            std::getline(file, line);
            std::istringstream issC(line);
            issC >> keyword >> C[0] >> C[1] >> C[2];

            // If faceCounter is even, assign a random color to the next two faces
            if (faceCounter % 1000 == 0)
            {
                color = getRandomColor(); // Generate random color
            }
            triangles.emplace_back(A, B, C, color);

            faceCounter++;
        }
    }

    file.close();
    return triangles;
}

