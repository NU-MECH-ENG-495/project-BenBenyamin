#include <vector>
#include <random>
#include <cmath>

float determinant3x3(const std::vector<float> &v1, const std::vector<float> &v2, const std::vector<float> &v3)
{
    // Determinant of the 3x3 matrix formed by v1, v2, v3
    return v1[0] * (v2[1] * v3[2] - v2[2] * v3[1]) -
           v1[1] * (v2[0] * v3[2] - v2[2] * v3[0]) +
           v1[2] * (v2[0] * v3[1] - v2[1] * v3[0]);
}


float dotProduct(const std::vector<float> &v1, const std::vector<float> &v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

float norm(const std::vector<float> &v1)
{
    return std::sqrt(dotProduct(v1,v1));
}

std::vector<std::vector<float>> calculateOrthonormals(const std::vector<float> &v1)
{
    float det = 0;
    std::vector<float> v2,v3;
    while (det == 0)
    // Get 2 Random vectors from the standard base
    {
        int index2 = rand() % 3;
        int index3 = rand() % 3;
    
        v2 = (index2 == 0) ? std::vector<float>{1.0f, 0.0f, 0.0f} :
             (index2 == 1) ? std::vector<float>{0.0f, 1.0f, 0.0f} : std::vector<float>{0.0f, 0.0f, 1.0f};
    
        v3 = (index3 == 0) ? std::vector<float>{1.0f, 0.0f, 0.0f} :
             (index3 == 1) ? std::vector<float>{0.0f, 1.0f, 0.0f} : std::vector<float>{0.0f, 0.0f, 1.0f};
    
        det = determinant3x3(v1, v2, v3);
    }

    // Gram–Schmidt process

    v2[0] -= dotProduct(v1,v2)*v1[0];
    v2[1] -= dotProduct(v1,v2)*v1[1];
    v2[2] -= dotProduct(v1,v2)*v1[2];

    float v2_norm = norm(v2);

    v2[0] /= v2_norm;
    v2[1] /= v2_norm;
    v2[2] /= v2_norm;

    v3[0] -= dotProduct(v1,v3)*v1[0] + dotProduct(v2,v3)*v3[0];
    v3[1] -= dotProduct(v1,v3)*v1[1] + dotProduct(v2,v3)*v3[1];
    v3[2] -= dotProduct(v1,v3)*v1[2] + dotProduct(v2,v3)*v3[2];

    float v3_norm = norm(v3);

    v3[0] /= v3_norm;
    v3[1] /= v3_norm;
    v3[2] /= v3_norm;

    return {v1, v2, v3};
}
