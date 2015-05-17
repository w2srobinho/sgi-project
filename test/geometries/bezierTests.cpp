#include "bezier.h"

#include "point.h"
#include <gtest/gtest.h>

TEST(BezierTests, quadraticBezier)
{
  geometries::Bezier bezier({
    new geometries::Point(5, 5),
    new geometries::Point(10, 10),
    new geometries::Point(15, 5)});

  auto bezierPoints = bezier.getBezierPoints(1u);

  std::vector<geometries::Point> expected = {
    geometries::Point(5, 5),
    geometries::Point(6, 5.9f),
    geometries::Point(7, 6.6f),
    geometries::Point(8, 7.1f),
    geometries::Point(9, 7.4f),
    geometries::Point(10, 7.5f),
    geometries::Point(11, 7.4f),
    geometries::Point(12, 7.1f),
    geometries::Point(13, 6.6f),
    geometries::Point(14, 5.9f),
    geometries::Point(15, 5)};

  ASSERT_EQ(expected.size(), bezierPoints.size());

  for (std::size_t i = 0; i < bezierPoints.size(); ++i)
    ASSERT_EQ(expected.at(i), bezierPoints.at(i));
}

TEST(BezierTests, cubicBezier)
{
  geometries::Bezier bezier({
    new geometries::Point(5, 5),
    new geometries::Point(10, 10),
    new geometries::Point(15, 5),
    new geometries::Point(20, 10)});

  auto bezierPoints = bezier.getBezierPoints(1u);

  std::vector<geometries::Point> expected = {
    geometries::Point(    5,     5),
    geometries::Point( 6.5f, 6.22f),
    geometries::Point(    8, 6.96f),
    geometries::Point( 9.5f, 7.34f),
    geometries::Point(   11, 7.48f),
    geometries::Point(12.5f,  7.5f),
    geometries::Point(   14, 7.52f),
    geometries::Point(15.5f, 7.66f),
    geometries::Point(   17, 8.04f),
    geometries::Point(18.5f, 8.78f),
    geometries::Point(   20,    10)};
  
  ASSERT_EQ(expected.size(), bezierPoints.size());

  for (std::size_t i = 0; i < bezierPoints.size(); ++i)
    ASSERT_EQ(expected.at(i), bezierPoints.at(i));
}
