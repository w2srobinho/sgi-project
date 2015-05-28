#include "window.h"

#include "point2D.h"
#include <gtest/gtest.h>


class WindowTests : public testing::Test
{
protected:
  void SetUp() override
  {
    window.reset(new Window(geometries::Point2D(0, 0), geometries::Point2D(50, 50)));
  }

  std::unique_ptr<Window> window;
};

TEST_F(WindowTests, zoomIn)
{
  window->zoomIn();
  ASSERT_LT(window->getMaxPoint(), geometries::Point2D(50, 50));
   //ASSERT_()
}