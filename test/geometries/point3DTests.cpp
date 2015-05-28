#include "point3D.h"

#include <gtest/gtest.h>

TEST(Point3DTests, productAssignOperator)
{
  geometries::Point3D p1(1.02f, 3.98f, 2);

  const float scale = 5;
  p1 *= scale;

  ASSERT_EQ(p1, geometries::Point3D(5.1f, 19.9f, 10));
  ASSERT_EQ(4u, p1.get().size());
}

TEST(Point3DTests, assignOperator)
{
  geometries::Point3D p;
  geometries::Point3D p1(1.02f, 3.98f, 2);

  ASSERT_EQ(geometries::Point3D(0, 0, 0), p);
  p = p1;

  ASSERT_EQ(p1, p); 
}

TEST(Point3DTests, equals)
{
  geometries::Point3D p1(1.01f, 3.98f, 2);
  geometries::Point3D p2(1.0f, 3.99f, 1.99f);

  ASSERT_EQ(p1, p2);

  float epsilon = 0.01f;
  ASSERT_TRUE(p1.equals(p2, epsilon));
}

TEST(Point3DTests, notEquals)
{
  geometries::Point3D p1(1.02f, 3.98f, 2);
  geometries::Point3D p2(1.0f, 3.95f, 1.99f);

  float epsilon = 0.03f;
  ASSERT_TRUE(p1.equals(p2, epsilon));

  ASSERT_NE(p1, p2);

  epsilon = 0.01f;
  ASSERT_FALSE(p1.equals(p2, epsilon));
}

TEST(Point3DTests, translation)
{
  geometries::Point3D p(1, 3, 2);
  float dx = -3.0;
  float dy = 2.0;
  float dz = 1.0;

  geometries::Point3D expected(-2, 5, 3);
  p.translation(dx, dy, dz);
  
  ASSERT_EQ(expected, p);
}

TEST(Point3DTests, scaling)
{
  geometries::Point3D p(4, 5, 2);
  float sx = 0.5;
  float sy = 0.5;
  float sz = 0.5;

  p.scaling(sx, sy, sz);

  geometries::Point3D expected(2, 2.5, 1);
  ASSERT_EQ(expected, p);
}

TEST(Point3DTests, rotateX)
{
  float angle = 30;
  geometries::Point3D p(2, 2.5, 2);

  p.rotateX(angle);

  geometries::Point3D expected(2, 1.16f, 2.98f);
  ASSERT_EQ(expected, p);
}

TEST(Point3DTests, rotateY)
{
  float angle = 30;
  geometries::Point3D p(2, 2.5, 2);

  p.rotateY(angle);

  geometries::Point3D expected(2.73f, 2.5, 0.73f);
  ASSERT_EQ(expected, p);
}

TEST(Point3DTests, rotateZ)
{
  float angle = 30;
  geometries::Point3D p(2, 2.5, 2);

  p.rotateZ(angle);

  geometries::Point3D expected(0.48f, 3.16f, 2);
  ASSERT_EQ(expected, p);
}