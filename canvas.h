#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>

class Canvas
{
private:
    int height;
    int width;
    std::vector<float> cameraNormal;
    std::vector<std::vector<std::vector<float>>> pixels;
    std::vector<std::vector<float>> depth;

public:
    Canvas(int h, int w);
    void putPixel(int x, int y, float depth, std::vector<float> &color);
    int getWidth();
    int getHeight();
    void writePPM(const std::string &filename);
    void setCameraNormal(std::vector<float> &normal);
    void clear();
    std::vector<float> getCameraNormal() const;
};

#endif // CANVAS_H
