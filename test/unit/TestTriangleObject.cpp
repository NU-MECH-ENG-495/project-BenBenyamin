/**
 * @file TestTriangleObject.cpp
 * @brief This file contains unit tests for the TriangleObject class using the Google Test framework.
 * 
 * The tests cover the functionality of the TriangleObject class, including its constructor, scaling,
 * translation, and rotation transformations. The TriangleObject class represents a collection of
 * TriangleSurface objects loaded from an STL file.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */

 #include <gtest/gtest.h> // Google Test framework
 #include <vector>
 #include "triangle_object.h"
 
 /**
  * @brief Test fixture for the TriangleObject class.
  * 
  * This fixture initializes a TriangleObject by loading an STL file containing two triangles.
  */
 class TriangleObjectTest : public ::testing::Test
 {
 protected:
     TriangleObjectTest() : triangleObj("../test/stl/two_triangles.stl") {} // Initialize TriangleObject with an STL file
 
     TriangleObject triangleObj; // The TriangleObject to be tested
 };
 
 /**
  * @brief Tests the TriangleObject constructor.
  * 
  * This test verifies that the TriangleObject is correctly initialized with the expected number of triangles.
  */
 TEST_F(TriangleObjectTest, ConstructorTest)
 {
     EXPECT_EQ(triangleObj.size(), 2); // Check that the STL file contains two triangles
 }
 
 /**
  * @brief Tests the `scale` method.
  * 
  * This test verifies that all triangles in the TriangleObject are correctly scaled by a given factor.
  */
 TEST_F(TriangleObjectTest, scaleTest)
 {
     triangleObj.scale(1.1); // Scale the TriangleObject by 1.1
 
     // Compare the vertices of the first triangle after scaling
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[0], 220);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[1], 220);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[2], 330);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[0], 330);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[1], 220);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[2], 330);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[0], 330);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[1], 330);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[2], 330);
 
     // Compare the vertices of the second triangle after scaling
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[0], 220);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[1], 220);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[2], 330);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[0], 330);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[1], 330);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[2], 330);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[0], 220);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[1], 330);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[2], 330);
 }
 
 /**
  * @brief Tests the `translate` method.
  * 
  * This test verifies that all triangles in the TriangleObject are correctly translated by a given offset.
  */
 TEST_F(TriangleObjectTest, translateTest)
 {
     triangleObj.translate(1, 1, 1); // Translate the TriangleObject by (1, 1, 1)
 
     // Compare the vertices of the first triangle after translation
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[0], 201);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[1], 201);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getA()[2], 301);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[0], 301);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[1], 201);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getB()[2], 301);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[0], 301);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[1], 301);
     EXPECT_EQ(triangleObj.getTriangles()->at(0).getC()[2], 301);
 
     // Compare the vertices of the second triangle after translation
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[0], 201);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[1], 201);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getA()[2], 301);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[0], 301);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[1], 301);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getB()[2], 301);
 
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[0], 201);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[1], 301);
     EXPECT_EQ(triangleObj.getTriangles()->at(1).getC()[2], 301);
 }
 
 /**
  * @brief Tests the `rotateAroundX` method.
  * 
  * This test verifies that all triangles in the TriangleObject are correctly rotated around the X-axis.
  */
 TEST_F(TriangleObjectTest, rotateXTest)
 {
     // Rotate the TriangleObject around the X-axis by 90 degrees using the first triangle's A vertex as the rotation point
     triangleObj.rotateAroundX(90, triangleObj.getTriangles()->at(0).getA());
     const double tolerance = 0.01;
 
     // Check the vertices of the first triangle after rotation
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[0], 0, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[1], 0, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[2], 0, tolerance);
     
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[0], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[1], -300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[2], 200, tolerance);
     
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[0], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[1], -300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[2], 300, tolerance);
 
     // Check the vertices of the second triangle after rotation
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
 
 /**
  * @brief Tests the `rotateAroundY` method.
  * 
  * This test verifies that all triangles in the TriangleObject are correctly rotated around the Y-axis.
  */
 TEST_F(TriangleObjectTest, rotateYTest)
 {
     // Rotate the TriangleObject around the Y-axis by 90 degrees using the first triangle's A vertex as the rotation point
     triangleObj.rotateAroundY(90, triangleObj.getTriangles()->at(0).getA());
     const double tolerance = 0.01;
 
     // Check the vertices of the first triangle after rotation
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[0], 0, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[1], 0, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[2], 0, tolerance);
     
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[0], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[1], 200, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[2], -300, tolerance);
     
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[0], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[1], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[2], -300, tolerance);
 
     // Check the vertices of the second triangle after rotation
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
 
 /**
  * @brief Tests the `rotateAroundZ` method.
  * 
  * This test verifies that all triangles in the TriangleObject are correctly rotated around the Z-axis.
  */
 TEST_F(TriangleObjectTest, rotateZTest)
 {
     // Rotate the TriangleObject around the Z-axis by 90 degrees using the first triangle's A vertex as the rotation point
     triangleObj.rotateAroundZ(90, triangleObj.getTriangles()->at(0).getA());
     const double tolerance = 0.01;
 
     // Check the vertices of the first triangle after rotation
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[0], 0, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[1], 0, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getA()[2], 0, tolerance);
     
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[0], -200, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[1], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getB()[2], 300, tolerance);
     
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[0], -300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[1], 300, tolerance);
     EXPECT_NEAR(triangleObj.getTriangles()->at(0).getC()[2], 300, tolerance);
 
     // Check the vertices of the second triangle after rotation
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