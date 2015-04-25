#include "window.h"

#include "point.h"
#include <gtest/gtest.h>


class WindowTests : public testing::Test
{
protected:
  void SetUp() override
  {
    window = std::make_unique<Window>(geometries::Point(0, 0), geometries::Point(50, 50));
  }

  std::unique_ptr<Window> window;
};

TEST_F(WindowTests, zoomIn)
{
  window->zoomIn();
  ASSERT_LT(window->getMaxPoint(), geometries::Point(50, 50));
   //ASSERT_()
}