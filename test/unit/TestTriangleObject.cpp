#include <gtest/gtest.h>
#include <vector>
#include "triangle_object.h"

class TriangleObjectTest : public ::testing::Test
{
protected:
    TriangleObjectTest() : triangleObj("../test/stl/two_triangles.stl") {}

    TriangleObject triangleObj;
};

TEST_F(TriangleObjectTest, ConstructorTest)
{
    EXPECT_EQ(triangleObj.size(), 2);
}

TEST_F(TriangleObjectTest, scaleTest)
{

    triangleObj.scale(1.1);


    // Compare A vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[0], 220);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[1], 220);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[2], 330);

    // Compare B vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[0], 330);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[1], 220);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[2], 330);

    // Compare C vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[0], 330);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[1], 330);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[2], 330);


    // Compare A vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[0], 220);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[1], 220);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[2], 330);

    // Compare B vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[0], 330);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[1], 330);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[2], 330);

    // Compare C vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[0], 220);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[1], 330);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[2], 330);

}

TEST_F(TriangleObjectTest, translateTest)
{

    triangleObj.translate(1,1,1);


    // Compare A vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[0], 201);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[1], 201);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[2], 301);

    // Compare B vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[0], 301);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[1], 201);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[2], 301);

    // Compare C vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[0], 301);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[1], 301);
    EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[2], 301);


    // Compare A vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[0], 201);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[1], 201);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[2], 301);

    // Compare B vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[0], 301);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[1], 301);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[2], 301);

    // Compare C vector element by element
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[0], 201);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[1], 301);
    EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[2], 301);

}

TEST_F(TriangleObjectTest, rotateXTest)
{
    // Rotate the triangle around the X-axis by 45 degrees using point A as the rotation point
    triangleObj.rotateAroundX(90, triangleObj.getTriangles()->at(0).getA());
    const double tolerance = 0.01;

    // A remains unchanged because it's the rotation point
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[0], 0, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[1], 0, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[2], 0, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[1], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[2], 200, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[1], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[2], 300, tolerance);

    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[0], 200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[1], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[2], 200, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[1], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[2], 300, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[0], 200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[1], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[2], 300, tolerance);
}

TEST_F(TriangleObjectTest, rotateYTest)
{
    // Rotate the triangle around the X-axis by 45 degrees using point A as the rotation point
    triangleObj.rotateAroundY(90, triangleObj.getTriangles()->at(0).getA());
    const double tolerance = 0.01;

    // A remains unchanged because it's the rotation point
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[0], 0, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[1], 0, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[2], 0, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[1], 200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[2], -300, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[1], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[2], -300, tolerance);

    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[1], 200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[2], -200, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[1], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[2], -300, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[0], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[1], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[2], -200, tolerance);
}

TEST_F(TriangleObjectTest, rotateZTest)
{
    // Rotate the triangle around the X-axis by 45 degrees using point A as the rotation point
    triangleObj.rotateAroundZ(90, triangleObj.getTriangles()->at(0).getA());
    const double tolerance = 0.01;

    // A remains unchanged because it's the rotation point
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[0], 0, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[1], 0, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[2], 0, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[0], -200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[1], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[2], 300, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[0], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[1], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[2], 300, tolerance);

    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[0], -200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[1], 200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getA()[2], 300, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[0], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[1], 300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getB()[2], 300, tolerance);
    
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[0], -300, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[1], 200, tolerance);
    EXPECT_NEAR(triangleObj.getTriangles()->at(1).getC()[2], 300, tolerance);
}