#include "point2D.h"

#include <gtest/gtest.h>

TEST(Point2DTests, productAssignOperator)
{
  geometries::Point2D p1(1.02f, 3.98f);

  const float scale = 5;
  p1 *= scale;

  ASSERT_EQ(p1, geometries::Point2D(5.09f, 19.9f));
  ASSERT_EQ(3u, p1.get().size());
}

TEST(Point2DTests, assignOperator)
{
  geometries::Point2D p;
  geometries::Point2D p1(1.02f, 3.98f);

  ASSERT_EQ(geometries::Point2D(0, 0), p);
  p = p1;

  ASSERT_EQ(p1, p); 
}

TEST(Point2DTests, equals)
{
  geometries::Point2D p1(1.01f, 3.98f);
  geometries::Point2D p2(1.0f, 3.99f);

  ASSERT_EQ(p1, p2);

  float epsilon = 0.01f;
  ASSERT_TRUE(p1.equals(p2, epsilon));
}

TEST(Point2DTests, notEquals)
{
  geometries::Point2D p1(1.02f, 3.98f);
  geometries::Point2D p2(1.0f, 3.95f);

  float epsilon = 0.03f;
  ASSERT_TRUE(p1.equals(p2, epsilon));

  ASSERT_NE(p1, p2);

  epsilon = 0.01f;
  ASSERT_FALSE(p1.equals(p2, epsilon));
}

TEST(Point2DTests, translation)
{
  geometries::Point2D p(1, 3);
  float dx = -3.0;
  float dy = 2.0;

  geometries::Point2D expected(-2, 5);
  p.translation(dx, dy);

  ASSERT_EQ(expected, p);
}

TEST(Point2DTests, scaling)
{
  geometries::Point2D p(4.0, 5.0);
  float sx = 0.5;
  float sy = 0.5;

  p.scaling(sx, sy);

  geometries::Point2D expected(2, 2.5);
  ASSERT_EQ(expected, p);
}

TEST(Point2DTests, rotate)
{
  float angle = 30;
  geometries::Point2D p(2.0, 2.5);

  p.rotate(angle);

  geometries::Point2D expected(2.98f, 1.16f);
  ASSERT_EQ(expected, p);
}