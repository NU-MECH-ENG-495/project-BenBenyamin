#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <cmath>
#include "canvas.h"

class Sphere {
    private:
        double radius;
        int x;
        int y;
        float z; // depth
        std::vector<float> color;
    
    public:
        Sphere(double r, int xPos, int yPos, float depth, std::vector<float> col)
            : radius(r), x(xPos), y(yPos), z(depth), color(col) {}
        
        void project(Canvas& c);
};

#endif // SPHERE_H
