#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "triangle.h"

std::vector<TriangleSurface> readSTL(const std::string &filename)
{
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

            triangles.emplace_back(A, B, C, color);
        }
    }

    file.close();
    return triangles;
}