#include <gtest/gtest.h>
#include <vector>
#include "triangle_object.h"

class TriangleObjectTest : public ::testing::Test
{
protected:
    TriangleObjectTest() : triangleObj("/home/ben/Documents/Courses/Winter-2025/CPP/Project/test/stl/single_triangle.stl") {}

    TriangleObject triangleObj;
};

TEST_F(TriangleObjectTest, ConstructorTest)
{
    EXPECT_EQ(triangleObj.size(), 1);
}
