#include "window.h"

#include "point.h"
#include <gtest/gtest.h>


class WindowTests : public testing::Test
{
protected:
  void SetUp() override
  {
    window.reset(new Window(geometries::Point(0, 0), geometries::Point(50, 50)));
  }

  std::unique_ptr<Window> window;
};

TEST_F(WindowTests, zoomIn)
{
  window->zoomIn();
  ASSERT_GT(50, window->getMaxPoint().getX());
  ASSERT_GT(50, window->getMaxPoint().getY());
}

TEST_F(WindowTests, zoomOut)
{
  window->zoomOut();
  ASSERT_LT(50, window->getMaxPoint().getX());
  ASSERT_LT(50, window->getMaxPoint().getY());
}