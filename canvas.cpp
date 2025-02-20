#include <vector>

class Canvas
{
    private:
        int height;
        int width;
        std::vector<std::vector<std::vector<float>>> pixels;

    public:
        Canvas(int h, int w) : height(h), width(w), pixels(h, std::vector<float>(w, 0.0)) {};
        
        void putPixel(int x, int y, std::vector<float> color)
        {
            if (x >= 0 && x < height && y >= 0 && y < width && color.size() == pixels[0][0].size())
            {
                this->pixels[x][y] = color;
            }
            else
            {
                throw "Invalid coordinates or color";
            }
        }
};