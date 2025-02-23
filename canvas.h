#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>

class Canvas
{
    private:
        int height;
        int width;
        std::vector<std::vector<std::vector<float>>> pixels;

    public:
        Canvas(int h, int w);
        void putPixel(int x, int y, std::vector<float> &color);
        int getWidth();
        int getHeight();
        void writePPM(const std::string& filename);
};

#endif // CANVAS_H
