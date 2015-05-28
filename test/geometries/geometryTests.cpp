#include "point2D.h"
#include "polygon.h"

#include <gtest/gtest.h>
#include <memory>

class GeometryTests 
  : public testing::Test
{
protected:
  void SetUp() override
  {
    triangle.reset(new geometries::Polygon(std::vector<geometries::Point2D*>({
        new geometries::Point2D(2, 6),
        new geometries::Point2D(2, 10),
        new geometries::Point2D(6, 8) 
    })));
  }

protected:
  std::unique_ptr<geometries::Polygon> triangle;
};

TEST_F(GeometryTests, translatePolygons)
{ 
  float dx = 4.0;
  float dy = -3.0;
  triangle->translation(dx, dy);

  geometries::Polygon expected({
    new geometries::Point2D(6, 3),
    new geometries::Point2D(6, 7),
    new geometries::Point2D(10, 5)
  });

  ASSERT_EQ(expected, *triangle);
}

TEST_F(GeometryTests, scalingTriangle)
{
  float sx = 2;
  float sy = 0.5;

  triangle->scaling(sx, sy);

  geometries::Polygon expected({
    new geometries::Point2D(0.66f, 7),
    new geometries::Point2D(0.66f, 9),
    new geometries::Point2D(8.66f, 8)
  });

  EXPECT_EQ(expected, *triangle);
}

TEST_F(GeometryTests, rotateTriangleAtOrigin)
{
  float angle = 30;
  triangle->rotate(angle);

  geometries::Polygon expected({
    new geometries::Point2D(1.17f, 6.93f),
    new geometries::Point2D(3.17f, 10.39f),
    new geometries::Point2D(5.64f, 6.66f)
  });

  EXPECT_EQ(expected, *triangle);
}

TEST_F(GeometryTests, rotateTriangleInAPoint)
{
  float angle = 30;
  geometries::Point2D rotatePoint(10, 5);
  triangle->rotate(rotatePoint, angle);

  geometries::Polygon expected({
    new geometries::Point2D(3.57f, 9.86f),
    new geometries::Point2D(5.57f, 13.33f),
    new geometries::Point2D(8.03f, 9.59f)
  });

  EXPECT_EQ(expected, *triangle);
}
