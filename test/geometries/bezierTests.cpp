#include "bezier.h"

#include "point2D.h"
#include <gtest/gtest.h>

TEST(BezierTests, quadraticBezier)
{
  geometries::Bezier bezier({
    new geometries::Point2D(5, 5),
    new geometries::Point2D(10, 10),
    new geometries::Point2D(15, 5)});

  auto bezierPoints = bezier.getBezierPoints(1u);

  std::vector<geometries::Point2D> expected = {
    geometries::Point2D(    5,     5),
    geometries::Point2D( 5.5f, 5.47f),
    geometries::Point2D(    6,  5.9f),
    geometries::Point2D( 6.5f, 6.27f),
    geometries::Point2D(    7,  6.6f),
    geometries::Point2D( 7.5f, 6.87f),
    geometries::Point2D(    8,  7.1f),
    geometries::Point2D( 8.5f, 7.27f),
    geometries::Point2D(    9,  7.4f),
    geometries::Point2D( 9.5f, 7.47f),
    geometries::Point2D(   10,  7.5f),
    geometries::Point2D(10.5f, 7.47f),
    geometries::Point2D(   11,  7.4f),
    geometries::Point2D(11.5f, 7.27f),
    geometries::Point2D(   12,  7.1f),
    geometries::Point2D(12.5f, 6.87f),
    geometries::Point2D(   13,  6.6f),
    geometries::Point2D(13.5f, 6.27f),
    geometries::Point2D(   14,  5.9f),
    geometries::Point2D(14.5f, 5.47f),
    geometries::Point2D(   15,     5) };

  ASSERT_EQ(expected.size(), bezierPoints.size());

  for (std::size_t i = 0; i < bezierPoints.size(); ++i)
    ASSERT_EQ(expected.at(i), bezierPoints.at(i));
}

TEST(BezierTests, cubicBezier)
{
  geometries::Bezier bezier({
    new geometries::Point2D(5, 5),
    new geometries::Point2D(10, 10),
    new geometries::Point2D(15, 5),
    new geometries::Point2D(20, 10)});

  auto bezierPoints = bezier.getBezierPoints(1u);

  std::vector<geometries::Point2D> expected = {
    geometries::Point2D(     5,     5),
    geometries::Point2D( 5.75f, 5.67f),
    geometries::Point2D(   6.5, 6.22f),
    geometries::Point2D( 7.25f, 6.64f),
    geometries::Point2D(     8, 6.96f),
    geometries::Point2D( 8.75f, 7.18f),
    geometries::Point2D(   9.5, 7.34f),
    geometries::Point2D(10.25f, 7.43f),
    geometries::Point2D(    11, 7.48f),
    geometries::Point2D(11.75f, 7.49f),
    geometries::Point2D(  12.5,   7.5),
    geometries::Point2D(13.25f, 7.50f),
    geometries::Point2D(    14, 7.52f),
    geometries::Point2D(14.75f, 7.56f),
    geometries::Point2D(  15.5, 7.66f),
    geometries::Point2D(16.25f, 7.81f),
    geometries::Point2D(    17, 8.04f),
    geometries::Point2D(17.75f, 8.35f),
    geometries::Point2D(  18.5, 8.78f),
    geometries::Point2D(19.25f, 9.32f),
    geometries::Point2D(    20,    10) };

  ASSERT_EQ(expected.size(), bezierPoints.size());

  for (std::size_t i = 0; i < bezierPoints.size(); ++i)
    ASSERT_EQ(expected.at(i), bezierPoints.at(i));
}
