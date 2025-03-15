#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

float determinant3x3(const std::vector<float> &v1, const std::vector<float> &v2, const std::vector<float> &v3)
{
    // Determinant of the 3x3 matrix formed by v1, v2, v3
    return v1[0] * (v2[1] * v3[2] - v2[2] * v3[1]) -
           v1[1] * (v2[0] * v3[2] - v2[2] * v3[0]) +
           v1[2] * (v2[0] * v3[1] - v2[1] * v3[0]);
}

float dotProduct(const std::vector<float> &v1, const std::vector<float> &v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float norm(const std::vector<float> &v1)
{
    return std::sqrt(dotProduct(v1, v1));
}

std::vector<std::vector<float>> calculateOrthonormals(const std::vector<float> &v1)
{
    float det = 0;
    std::vector<float> v2, v3;
    while (det == 0)
    // Get 2 Random vectors from the standard base
    {
        int index2 = rand() % 3;
        int index3 = rand() % 3;

        v2 = (index2 == 0) ? std::vector<float>{1.0f, 0.0f, 0.0f} : (index2 == 1) ? std::vector<float>{0.0f, 1.0f, 0.0f}
                                                                                  : std::vector<float>{0.0f, 0.0f, 1.0f};

        v3 = (index3 == 0) ? std::vector<float>{1.0f, 0.0f, 0.0f} : (index3 == 1) ? std::vector<float>{0.0f, 1.0f, 0.0f}
                                                                                  : std::vector<float>{0.0f, 0.0f, 1.0f};

        det = determinant3x3(v1, v2, v3);
    }

    // Gram–Schmidt process

    v2[0] -= dotProduct(v1, v2) * v1[0];
    v2[1] -= dotProduct(v1, v2) * v1[1];
    v2[2] -= dotProduct(v1, v2) * v1[2];

    float v2_norm = norm(v2);

    v2[0] /= v2_norm;
    v2[1] /= v2_norm;
    v2[2] /= v2_norm;

    v3[0] -= dotProduct(v1, v3) * v1[0] + dotProduct(v2, v3) * v3[0];
    v3[1] -= dotProduct(v1, v3) * v1[1] + dotProduct(v2, v3) * v3[1];
    v3[2] -= dotProduct(v1, v3) * v1[2] + dotProduct(v2, v3) * v3[2];

    float v3_norm = norm(v3);

    v3[0] /= v3_norm;
    v3[1] /= v3_norm;
    v3[2] /= v3_norm;

    std::vector<std::vector<float>> result = {v2, v3};

    std::sort(result.begin(), result.end(), [](const std::vector<float> &a, const std::vector<float> &b)
              {
        // Compare the vectors lexicographically: first by x, then by y, then by z
        if (a[0] != b[0]) return a[0] < b[0];
        if (a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2]; });

    return {result[1], result[0]};
}


std::pair<std::pair<float, float>, std::pair<float, float>> calculateDotProductExtremes
(
    const std::vector<float>& projectedA, const std::vector<float>& projectedB, const std::vector<float>& projectedC, 
    const std::vector<std::vector<float>>& cameraAxis)
{
    // Calculate dot products with cameraAxis[1] and cameraAxis[2] for projected points
    float dotA1 = dotProduct(projectedA, cameraAxis[1]);
    float dotA2 = dotProduct(projectedA, cameraAxis[2]);

    float dotB1 = dotProduct(projectedB, cameraAxis[1]);
    float dotB2 = dotProduct(projectedB, cameraAxis[2]);

    float dotC1 = dotProduct(projectedC, cameraAxis[1]);
    float dotC2 = dotProduct(projectedC, cameraAxis[2]);
 
    // Calculate the min and max i,j values for the projections
    float minDot1 = std::min({dotA1, dotB1, dotC1});
    float maxDot1 = std::max({dotA1, dotB1, dotC1});

    float minDot2 = std::min({dotA2, dotB2, dotC2});
    float maxDot2 = std::max({dotA2, dotB2, dotC2});

    // Return the results as a pair of pairs
    return std::make_pair(std::make_pair(minDot1, maxDot1), std::make_pair(minDot2, maxDot2));
}
