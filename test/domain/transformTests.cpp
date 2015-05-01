#include "transform.h"

#include "point.h"
#include "polygon.h"

#include <gtest/gtest.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

class TransformTests 
  : public testing::Test
{
protected:
  void SetUp() override
  {
    triangle.reset(new geometries::Polygon(std::vector<geometries::Point*>({
        new geometries::Point(2, 6),
        new geometries::Point(2, 10),
        new geometries::Point(6, 8) 
    })));
  }

protected:
  std::unique_ptr<geometries::Geometry> triangle;
};

TEST_F(TransformTests, translation) 
{
  geometries::Point p(1, 3);
  float dx = -3.0;
  float dy = 2.0;

  std::vector<float> expected = { -2., 5., 1. };
  auto pointTransformed = transform::translation(p.get(), dx, dy);

  for (std::size_t i = 0; i < pointTransformed.get().size(); ++i)
  {
    ASSERT_NEAR(expected.at(i), pointTransformed.get().at(i), 0.01);
  }
}

TEST_F(TransformTests, translatePolygons)
{ 
  float dx = 4.0;
  float dy = -3.0;
  transform::translation(triangle.get(), dx, dy);

  geometries::Point expectedP1(6, 3);
  geometries::Point expectedP2(6, 7);
  geometries::Point expectedP3(10, 5);

  ASSERT_EQ(3, triangle->getPoints().size());
  ASSERT_EQ(expectedP1, *triangle->getPoints().at(0));
  ASSERT_EQ(expectedP2, *triangle->getPoints().at(1));
  ASSERT_EQ(expectedP3, *triangle->getPoints().at(2));
}

TEST_F(TransformTests, scaling)
{
  geometries::Point p(4.0, 5.0);
  float sx = 0.5;
  float sy = 0.5;

  std::vector<float> expected = { 2.0, 2.5, 1.0 };
  auto pointTransformed = transform::scaling(p.get(), sx, sy);

  for (std::size_t i = 0; i < pointTransformed.get().size(); ++i)
  {
    ASSERT_NEAR(expected.at(i), pointTransformed.get().at(i), 0.01);
  }
}

TEST_F(TransformTests, rotate)
{
  float angle = static_cast<float>(M_PI / 6);
  geometries::Point p(2.0, 2.5);

  std::vector<float> expected = { 2.98f, 1.16f, 1.0 };
  auto pointTransformed = transform::rotate(p.get(), angle);

  for (std::size_t i = 0; i < pointTransformed.get().size(); ++i)
  {
    ASSERT_NEAR(expected.at(i), pointTransformed.get().at(i), 0.01);
  }
}
