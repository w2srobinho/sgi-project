#include "point.h"

#include <gtest/gtest.h>

TEST(PointTests, productAssignOperator)
{
  geometries::Point p1(1.02f, 3.98f);

  const float scale = 5;
  p1 *= scale;

  ASSERT_EQ(p1, geometries::Point(5.09f, 19.9f));
  ASSERT_EQ(3u, p1.get().size());
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

TEST(PointTests, translation)
{
  geometries::Point p(1, 3);
  float dx = -3.0;
  float dy = 2.0;

  geometries::Point expected(-2, 5);
  p.translation(dx, dy);

  ASSERT_EQ(expected, p);
}

TEST(PointTests, scaling)
{
  geometries::Point p(4.0, 5.0);
  float sx = 0.5;
  float sy = 0.5;

  p.scaling(sx, sy);

  geometries::Point expected(2, 2.5);
  ASSERT_EQ(expected, p);
}

TEST(PointTests, rotate)
{
  float angle = 30;
  geometries::Point p(2.0, 2.5);

  p.rotate(angle);

  geometries::Point expected(2.98f, 1.16f);
  ASSERT_EQ(expected, p);
}