
#include <vector>
#include "canvas.h"

class TriangleSurface
{
private:

    std::vector<float> A; //first point of the triangle
    std::vector<float> B; //second point of the triangle
    std::vector<float> C; //third point of the triangle
    std::vector<float> color;
    
    public:

        void project(Canvas &c); //projects a triangle onto a canvas

};