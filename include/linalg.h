#ifndef LINALG_H
#define LINALG_H

#include <vector>

// Function to calculate the determinant of a 3x3 matrix formed by three vectors
float determinant3x3(const std::vector<float> &v1, const std::vector<float> &v2, const std::vector<float> &v3);

// Function to calculate the dot product of two vectors
float dotProduct(const std::vector<float> &v1, const std::vector<float> &v2);

// Function to calculate the norm (magnitude) of a vector
float norm(const std::vector<float> &v1);

// Function to calculate the orthonormal basis using the Gram-Schmidt process
std::vector<std::vector<float>> calculateOrthonormals(const std::vector<float> &v1);

std::pair<std::pair<float, float>, std::pair<float, float>> calculateDotProductExtremes
(
    const std::vector<float>& projectedA, const std::vector<float>& projectedB, const std::vector<float>& projectedC, 
    const std::vector<std::vector<float>>& cameraAxis
);

#endif // LINALG_H
