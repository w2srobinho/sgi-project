#include "transform.h"

#include "gmock/gmock.h"
#include "point.h"

TEST(transformTests, translation) {
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

TEST(transformTests, scaling)
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
