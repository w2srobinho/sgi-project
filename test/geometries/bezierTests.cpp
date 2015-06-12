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
    geometries::Point(    5,     5),
    geometries::Point( 5.5f, 5.47f),
    geometries::Point(    6,  5.9f),
    geometries::Point( 6.5f, 6.27f),
    geometries::Point(    7,  6.6f),
    geometries::Point( 7.5f, 6.87f),
    geometries::Point(    8,  7.1f),
    geometries::Point( 8.5f, 7.27f),
    geometries::Point(    9,  7.4f),
    geometries::Point( 9.5f, 7.47f),
    geometries::Point(   10,  7.5f),
    geometries::Point(10.5f, 7.47f),
    geometries::Point(   11,  7.4f),
    geometries::Point(11.5f, 7.27f),
    geometries::Point(   12,  7.1f),
    geometries::Point(12.5f, 6.87f),
    geometries::Point(   13,  6.6f),
    geometries::Point(13.5f, 6.27f),
    geometries::Point(   14,  5.9f),
    geometries::Point(14.5f, 5.47f),
    geometries::Point(   15,     5) };

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
    geometries::Point(     5,     5),
    geometries::Point( 5.75f, 5.67f),
    geometries::Point(   6.5, 6.22f),
    geometries::Point( 7.25f, 6.64f),
    geometries::Point(     8, 6.96f),
    geometries::Point( 8.75f, 7.18f),
    geometries::Point(   9.5, 7.34f),
    geometries::Point(10.25f, 7.43f),
    geometries::Point(    11, 7.48f),
    geometries::Point(11.75f, 7.49f),
    geometries::Point(  12.5,   7.5),
    geometries::Point(13.25f, 7.50f),
    geometries::Point(    14, 7.52f),
    geometries::Point(14.75f, 7.56f),
    geometries::Point(  15.5, 7.66f),
    geometries::Point(16.25f, 7.81f),
    geometries::Point(    17, 8.04f),
    geometries::Point(17.75f, 8.35f),
    geometries::Point(  18.5, 8.78f),
    geometries::Point(19.25f, 9.32f),
    geometries::Point(    20,    10) };

  ASSERT_EQ(expected.size(), bezierPoints.size());

  for (std::size_t i = 0; i < bezierPoints.size(); ++i)
    ASSERT_EQ(expected.at(i), bezierPoints.at(i));
}
