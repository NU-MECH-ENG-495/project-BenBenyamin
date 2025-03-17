#include <gtest/gtest.h>
#include <vector>
#include "triangle.h"

class TriangleTest : public ::testing::Test
{
protected:
    TriangleTest() : triangle({300, 300, 300}, {400, 300, 300}, {400, 400, 300}, {1, 0, 0}) {} // Initialize a red triangle

    TriangleSurface triangle;
};

TEST_F(TriangleTest, ConstructorTest)
{
    // Compare A vector element by element
    EXPECT_EQ(triangle.getA()[0], 300);
    EXPECT_EQ(triangle.getA()[1], 300);
    EXPECT_EQ(triangle.getA()[2], 300);

    // Compare B vector element by element
    EXPECT_EQ(triangle.getB()[0], 400);
    EXPECT_EQ(triangle.getB()[1], 300);
    EXPECT_EQ(triangle.getB()[2], 300);

    // Compare C vector element by element
    EXPECT_EQ(triangle.getC()[0], 400);
    EXPECT_EQ(triangle.getC()[1], 400);
    EXPECT_EQ(triangle.getC()[2], 300);

    // Compare color vector element by element
    EXPECT_EQ(triangle.getColor()[0], 1);
    EXPECT_EQ(triangle.getColor()[1], 0);
    EXPECT_EQ(triangle.getColor()[2], 0);
}

TEST_F(TriangleTest , projectPointToPlane_isInsideTest)
{

    
    std::vector<float> projectedA = triangle.projectPointToPlane(triangle.getA(), {0,0,1});
    std::vector<float> projectedB = triangle.projectPointToPlane(triangle.getB(), {0,0,1});
    std::vector<float> projectedC = triangle.projectPointToPlane(triangle.getC(), {0,0,1});
    std::vector<float> point = {300 , 300};
    std::vector<float> origin = {0 , 0};
    
    EXPECT_TRUE(triangle.isInside(origin, projectedA, projectedB, projectedC).empty());
    EXPECT_FALSE(triangle.isInside(point, projectedA, projectedB, projectedC).empty());
}

TEST_F(TriangleTest , scaleTest)
{   

    triangle.scale(1.1);

    // Compare A vector element by element
    EXPECT_EQ(triangle.getA()[0], 330);
    EXPECT_EQ(triangle.getA()[1], 330);
    EXPECT_EQ(triangle.getA()[2], 330);

    // Compare B vector element by element
    EXPECT_EQ(triangle.getB()[0], 440);
    EXPECT_EQ(triangle.getB()[1], 330);
    EXPECT_EQ(triangle.getB()[2], 330);

    // Compare C vector element by element
    EXPECT_EQ(triangle.getC()[0], 440);
    EXPECT_EQ(triangle.getC()[1], 440);
    EXPECT_EQ(triangle.getC()[2], 330);

} 

TEST_F(TriangleTest , translateTest)
{   

    triangle.translate(1,1,1);

    // Compare A vector element by element
    EXPECT_EQ(triangle.getA()[0], 301);
    EXPECT_EQ(triangle.getA()[1], 301);
    EXPECT_EQ(triangle.getA()[2], 301);

    // Compare B vector element by element
    EXPECT_EQ(triangle.getB()[0], 401);
    EXPECT_EQ(triangle.getB()[1], 301);
    EXPECT_EQ(triangle.getB()[2], 301);

    // Compare C vector element by element
    EXPECT_EQ(triangle.getC()[0], 401);
    EXPECT_EQ(triangle.getC()[1], 401);
    EXPECT_EQ(triangle.getC()[2], 301);

} 

TEST_F(TriangleTest, rotateXTest)
{
    // Rotate the triangle around the X-axis by 45 degrees using point A as the rotation point
    triangle.rotateAroundX(90, triangle.getA());
    const double tolerance = 0.01;

    // A remains unchanged because it's the rotation point
    EXPECT_NEAR(triangle.getA()[0], 0, tolerance);
    EXPECT_NEAR(triangle.getA()[1], 0, tolerance);
    EXPECT_NEAR(triangle.getA()[2], 0, tolerance);
    
    EXPECT_NEAR(triangle.getB()[0], 400, tolerance);
    EXPECT_NEAR(triangle.getB()[1], -300, tolerance);
    EXPECT_NEAR(triangle.getB()[2], 300, tolerance);
    
    EXPECT_NEAR(triangle.getC()[0], 400, tolerance);
    EXPECT_NEAR(triangle.getC()[1], -300, tolerance);
    EXPECT_NEAR(triangle.getC()[2], 400, tolerance);
}

TEST_F(TriangleTest, rotateYTest)
{
    // Rotate the triangle around the X-axis by 45 degrees using point A as the rotation point
    triangle.rotateAroundY(90, triangle.getA());
    const double tolerance = 0.01;

    // A remains unchanged because it's the rotation point
    EXPECT_NEAR(triangle.getA()[0], 0, tolerance);
    EXPECT_NEAR(triangle.getA()[1], 0, tolerance);
    EXPECT_NEAR(triangle.getA()[2], 0, tolerance);
    
    EXPECT_NEAR(triangle.getB()[0], 300, tolerance);
    EXPECT_NEAR(triangle.getB()[1], 300, tolerance);
    EXPECT_NEAR(triangle.getB()[2], -400, tolerance);
    
    EXPECT_NEAR(triangle.getC()[0], 300, tolerance);
    EXPECT_NEAR(triangle.getC()[1], 400, tolerance);
    EXPECT_NEAR(triangle.getC()[2], -400, tolerance);
}

TEST_F(TriangleTest, rotateZTest)
{
    // Rotate the triangle around the X-axis by 45 degrees using point A as the rotation point
    triangle.rotateAroundZ(90, triangle.getA());
    const double tolerance = 0.01;

    // A remains unchanged because it's the rotation point
    EXPECT_NEAR(triangle.getA()[0], 0, tolerance);
    EXPECT_NEAR(triangle.getA()[1], 0, tolerance);
    EXPECT_NEAR(triangle.getA()[2], 0, tolerance);
    
    EXPECT_NEAR(triangle.getB()[0], -300, tolerance);
    EXPECT_NEAR(triangle.getB()[1], 400, tolerance);
    EXPECT_NEAR(triangle.getB()[2], 300, tolerance);
    
    EXPECT_NEAR(triangle.getC()[0], -400, tolerance);
    EXPECT_NEAR(triangle.getC()[1], 400, tolerance);
    EXPECT_NEAR(triangle.getC()[2], 300, tolerance);
}
