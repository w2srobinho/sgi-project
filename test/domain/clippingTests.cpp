#include "clipping.h"

#include "line.h"
#include "point.h"

#include <gtest/gtest.h>
#include <memory>

class CohenSutherlandTest
  : public testing::Test
{
protected:
  void SetUp() override
  {
    geometries::Point minVpPoint(0, 0);
    geometries::Point maxVpPoint(10, 10);

    sutherland.reset(new clipping::CohenSutherland(minVpPoint, maxVpPoint));
  }

protected:
  std::unique_ptr<clipping::CohenSutherland> sutherland;
};

TEST_F(CohenSutherlandTest, LineClippingLeft)
{
  geometries::Line line(new geometries::Point(-2, 5), new geometries::Point(5, 5), "Line");
  
  std::vector<geometries::Point> expected = {
    geometries::Point(0, 5), 
    geometries::Point(5, 5) 
  };

  auto lineClipped = sutherland->lineClip(line.getP1(), line.getP2());

  for (std::size_t i = 0; i < lineClipped.size(); ++i)
  {
    ASSERT_EQ(expected.at(i), lineClipped.at(i));
  }
}

TEST_F(CohenSutherlandTest, LineClippingTop)
{
  geometries::Line line(new geometries::Point(5, -2), new geometries::Point(5, 5), "Line");

  std::vector<geometries::Point> expected = {
    geometries::Point(5, 0),
    geometries::Point(5, 5)
  };

  auto lineClipped = sutherland->lineClip(line.getP1(), line.getP2());

  for (std::size_t i = 0; i < lineClipped.size(); ++i)
  {
    ASSERT_EQ(expected.at(i), lineClipped.at(i));
  }
}

TEST_F(CohenSutherlandTest, LineClippingRight)
{
  geometries::Line line(new geometries::Point(5, 5), new geometries::Point(12, 5), "Line");

  std::vector<geometries::Point> expected = {
    geometries::Point(5, 5),
    geometries::Point(10, 5)
  };

  auto lineClipped = sutherland->lineClip(line.getP1(), line.getP2());

  for (std::size_t i = 0; i < lineClipped.size(); ++i)
  {
    ASSERT_EQ(expected.at(i), lineClipped.at(i));
  }
}

TEST_F(CohenSutherlandTest, LineClippingBottom)
{
  geometries::Line line(new geometries::Point(5, 5), new geometries::Point(5, 12), "Line");

  std::vector<geometries::Point> expected = {
    geometries::Point(5, 5),
    geometries::Point(5, 10)
  };

  auto lineClipped = sutherland->lineClip(line.getP1(), line.getP2());

  for (std::size_t i = 0; i < lineClipped.size(); ++i)
  {
    ASSERT_EQ(expected.at(i), lineClipped.at(i));
  }
}

TEST_F(CohenSutherlandTest, LineClippingInside)
{
  geometries::Line line(new geometries::Point(2, 5), new geometries::Point(7, 5), "Line");

  std::vector<geometries::Point> expected = {
    geometries::Point(2, 5),
    geometries::Point(7, 5)
  };

  auto lineClipped = sutherland->lineClip(line.getP1(), line.getP2());

  for (std::size_t i = 0; i < lineClipped.size(); ++i)
  {
    ASSERT_EQ(expected.at(i), lineClipped.at(i));
  }
}

TEST_F(CohenSutherlandTest, LineClippingLeft2Top)
{
  geometries::Line line(new geometries::Point(-2, 7), new geometries::Point(7, -2), "Line");

  std::vector<geometries::Point> expected = {
    geometries::Point(0, 5),
    geometries::Point(5, 0)
  };

  auto lineClipped = sutherland->lineClip(line.getP1(), line.getP2());

  for (std::size_t i = 0; i < lineClipped.size(); ++i)
  {
    ASSERT_EQ(expected.at(i), lineClipped.at(i));
  }
}
