#include "point.h"

#include <gtest/gtest.h>

TEST(Point3dTests, productAssignOperator)
{
  geometries::Point p1(1.02f, 3.98f, 2);

  const float scale = 5;
  p1 *= scale;

  ASSERT_EQ(p1, geometries::Point(5.1f, 19.9f, 10));
  ASSERT_EQ(4u, p1.get().size());
}

TEST(Point3dTests, assignOperator)
{
  geometries::Point p;
  geometries::Point p1(1.02f, 3.98f, 2);

  ASSERT_EQ(geometries::Point(0, 0, 0), p);
  p = p1;

  ASSERT_EQ(p1, p); 
}

TEST(Point3dTests, equals)
{
  geometries::Point p1(1.01f, 3.98f, 2);
  geometries::Point p2(1.0f, 3.99f, 1.99f);

  ASSERT_EQ(p1, p2);

  float epsilon = 0.01f;
  ASSERT_TRUE(p1.equals(p2, epsilon));
}

TEST(Point3dTests, notEquals)
{
  geometries::Point p1(1.02f, 3.98f, 2);
  geometries::Point p2(1.0f, 3.95f, 1.99f);

  float epsilon = 0.03f;
  ASSERT_TRUE(p1.equals(p2, epsilon));

  ASSERT_NE(p1, p2);

  epsilon = 0.01f;
  ASSERT_FALSE(p1.equals(p2, epsilon));
}

TEST(Point3dTests, translation)
{
  geometries::Point p(1, 3, 2);
  float dx = -3.0;
  float dy = 2.0;
  float dz = 1.0;

  geometries::Point expected(-2, 5, 3);
  p.translation(dx, dy, dz);
  
  ASSERT_EQ(expected, p);
}

TEST(Point3dTests, scaling)
{
  geometries::Point p(4, 5, 2);
  float sx = 0.5;
  float sy = 0.5;
  float sz = 0.5;

  p.scaling(sx, sy, sz);

  geometries::Point expected(2, 2.5, 1);
  ASSERT_EQ(expected, p);
}

TEST(Point3dTests, rotateX)
{
  float angle = 30;
  geometries::Point p(2, 2.5, 2);

  p.rotateX(angle);

  geometries::Point expected(2, 1.16f, 2.98f);
  ASSERT_EQ(expected, p);
}

TEST(Point3dTests, rotateY)
{
  float angle = 30;
  geometries::Point p(2, 2.5, 2);

  p.rotateY(angle);

  geometries::Point expected(2.73f, 2.5, 0.73f);
  ASSERT_EQ(expected, p);
}

TEST(Point3dTests, rotateZ)
{
  float angle = 30;
  geometries::Point p(2, 2.5, 2);

  p.rotateZ(angle);

  geometries::Point expected(0.48f, 3.16f, 2);
  ASSERT_EQ(expected, p);
}