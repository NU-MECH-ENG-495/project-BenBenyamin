/**
 * @file TestTriangle.cpp
 * @brief This file contains unit tests for the TriangleSurface class using the Google Test framework.
 * 
 * The tests cover the functionality of the TriangleSurface class, including its constructor, point projection,
 * point containment checks, scaling, translation, and rotation transformations.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */

 #include <gtest/gtest.h> // Google Test framework
 #include <vector>
 #include "triangle.h"
 
 /**
  * @brief Test fixture for the TriangleSurface class.
  * 
  * This fixture initializes a red triangle with specific vertices for use in all test cases.
  */
 class TriangleTest : public ::testing::Test
 {
 protected:
     TriangleTest() : triangle({300, 300, 300}, {400, 300, 300}, {400, 400, 300}, {1, 0, 0}) {} // Initialize a red triangle
 
     TriangleSurface triangle; // The triangle object to be tested
 };
 
 /**
  * @brief Tests the TriangleSurface constructor.
  * 
  * This test verifies that the triangle is initialized with the correct vertices and color.
  */
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
 
 /**
  * @brief Tests the `projectPointToPlane` and `isInside` methods.
  * 
  * This test verifies that points are correctly projected onto a plane and that the `isInside` method
  * correctly determines whether a point lies inside the projected triangle.
  */
 TEST_F(TriangleTest, projectPointToPlane_isInsideTest)
 {
     // Project the triangle's vertices onto a plane with normal {0, 0, 1}
     std::vector<float> projectedA = triangle.projectPointToPlane(triangle.getA(), {0, 0, 1});
     std::vector<float> projectedB = triangle.projectPointToPlane(triangle.getB(), {0, 0, 1});
     std::vector<float> projectedC = triangle.projectPointToPlane(triangle.getC(), {0, 0, 1});
 
     std::vector<float> point = {300, 300}; // A point inside the triangle
     std::vector<float> origin = {0, 0};    // A point outside the triangle
 
     // Test that the origin is not inside the triangle
     EXPECT_TRUE(triangle.isInside(origin, projectedA, projectedB, projectedC).empty());
 
     // Test that the point {300, 300} is inside the triangle
     EXPECT_FALSE(triangle.isInside(point, projectedA, projectedB, projectedC).empty());
 }
 
 /**
  * @brief Tests the `scale` method.
  * 
  * This test verifies that the triangle is correctly scaled by a given factor.
  */
 TEST_F(TriangleTest, scaleTest)
 {
     triangle.scale(1.1); // Scale the triangle by 1.1
 
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
 
 /**
  * @brief Tests the `translate` method.
  * 
  * This test verifies that the triangle is correctly translated by a given offset.
  */
 TEST_F(TriangleTest, translateTest)
 {
     triangle.translate(1, 1, 1); // Translate the triangle by (1, 1, 1)
 
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
 
 /**
  * @brief Tests the `rotateAroundX` method.
  * 
  * This test verifies that the triangle is correctly rotated around the X-axis by a given angle.
  */
 TEST_F(TriangleTest, rotateXTest)
 {
     // Rotate the triangle around the X-axis by 90 degrees using point A as the rotation point
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
 
 /**
  * @brief Tests the `rotateAroundY` method.
  * 
  * This test verifies that the triangle is correctly rotated around the Y-axis by a given angle.
  */
 TEST_F(TriangleTest, rotateYTest)
 {
     // Rotate the triangle around the Y-axis by 90 degrees using point A as the rotation point
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
 
 /**
  * @brief Tests the `rotateAroundZ` method.
  * 
  * This test verifies that the triangle is correctly rotated around the Z-axis by a given angle.
  */
 TEST_F(TriangleTest, rotateZTest)
 {
     // Rotate the triangle around the Z-axis by 90 degrees using point A as the rotation point
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