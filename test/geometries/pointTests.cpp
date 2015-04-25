#include "point.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <gtest/gtest.h>



TEST(PointTests, productAssignOperator)
{
  geometries::Point p1(1.02f, 3.98f);

  const float scale = 5;
  p1 *= scale;

  ASSERT_EQ(p1, geometries::Point(5.09f, 19.9f));
  ASSERT_EQ(3, p1.get().size());
}

TEST(PointTests, assignOperator)
{
  geometries::Point p;
  geometries::Point p1(1.02f, 3.98f);

  ASSERT_EQ(geometries::Point(0, 0), p);
  p = p1;

  ASSERT_EQ(p1, p); 
}

TEST(PointTests, equals)
{
  geometries::Point p1(1.01f, 3.98f);
  geometries::Point p2(1.0f, 3.99f);

  ASSERT_EQ(p1, p2);

  float epsilon = 0.01f;
  ASSERT_TRUE(p1.equals(p2, epsilon));
}

TEST(PointTests, notEquals)
{
  geometries::Point p1(1.02f, 3.98f);
  geometries::Point p2(1.0f, 3.95f);

  float epsilon = 0.03f;
  ASSERT_TRUE(p1.equals(p2, epsilon));

  ASSERT_NE(p1, p2);

  epsilon = 0.01f;
  ASSERT_FALSE(p1.equals(p2, epsilon));
}
