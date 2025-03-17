#include <gtest/gtest.h>
#include "canvas.h"
#include <vector>

class CanvasTest : public ::testing::Test
{
protected:
    CanvasTest() : canvas(100, 100) {} // Initialize a 100x100 canvas

    Canvas canvas;
};

TEST_F(CanvasTest, ConstructorTest) 
{
    EXPECT_EQ(canvas.getHeight(), 100);
    EXPECT_EQ(canvas.getWidth(), 100);
}

TEST_F(CanvasTest, SetGetCameraNormalTest)
{
    // Set the camera normal to a specific value and test if it's correctly set
    std::vector<float> normal = {0.0f, 1.0f, 0.0f}; // Example camera normal
    canvas.setCameraNormal(normal);

    // Test that the camera normal is correctly set
    EXPECT_EQ(canvas.getCameraNormal(), normal);
}


TEST_F(CanvasTest, ClearCanvasTest)
{
    std::vector<float> redColor = {1.0f, 0.0f, 0.0f};  // Create a named vector for color
    canvas.putPixel(10, 10, 0.5f, redColor); // Set a red pixel

    canvas.clear(); // Reset canvas

    const auto& pixels = canvas.getPixels();
    const auto& depth = canvas.getDepthBuffer();

    // Manually compare each color component of the pixel
    for (size_t i = 0; i < redColor.size(); ++i)
    {
        EXPECT_FLOAT_EQ(pixels[10][10][i], 0.0) 
            << "Pixel at (10,10)[" << i << "] was not reset to black";
    }

    // Check if (10,10) depth is reset
    EXPECT_FLOAT_EQ(depth[10][10], 0.0) 
        << "Depth at (10,10) was not reset";
}



TEST_F(CanvasTest, PutPixelTest)
{
    // Test putting a pixel at a specific location
    std::vector<float> color = {1.0f, 0.0f, 0.0f}; // Red color
    float depth = 0.5f;

    canvas.putPixel(10, 20, depth, color);

    // Test that the pixel at (10, 20) has the correct color and depth
    // This would require an appropriate getter for pixel data; for example:
    // EXPECT_EQ(canvas.getPixel(10, 20), std::make_pair(depth, color));
    // The method to retrieve pixel data needs to be implemented in the Canvas class.
}

TEST_F(CanvasTest, WritePPMTest)
{
    // Test that the writePPM method does not throw any errors and successfully writes a file
    // We will just check if no exceptions are thrown during the call.
    EXPECT_NO_THROW(canvas.writePPM("test_output.ppm"));
}

TEST_F(CanvasTest, CameraAxisTest)
{
    std::vector<float> normal = {1.0f, 0.0f, 0.0f}; // Example camera normal
    canvas.setCameraNormal(normal);
    // Test the camera axis retrieval
    std::vector<std::vector<float>> cameraAxis = canvas.getCameraAxis();

    // Assuming you know the expected result based on the default camera orientation
    EXPECT_EQ(cameraAxis.size(), 3);                                  // Should have 3 axis
    EXPECT_EQ(cameraAxis[0], std::vector<float>({1.0f, 0.0f, 0.0f})); // Example X-axis
    EXPECT_EQ(cameraAxis[1], std::vector<float>({0.0f, 1.0f, 0.0f})); // Example Y-axis
    EXPECT_EQ(cameraAxis[2], std::vector<float>({0.0f, 0.0f, 1.0f})); // Example Z-axis
}
