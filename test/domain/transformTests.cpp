#include "transform.h"

#include "gmock/gmock.h"
#include "point.h"

TEST(transformTests, translation) {
  geometries::Point p(1, 3);
  float dx = -3.0;
  float dy = 2.0;

  auto pointTransformed = transform::translation(p.get(), dx, dy);

  std::vector<float> expected = { -2., 5., 1. };
  for (std::size_t i = 0; i < pointTransformed.size(); ++i)
  {
    ASSERT_NEAR(expected.at(i), pointTransformed.at(i), 0.01);
  }
}
