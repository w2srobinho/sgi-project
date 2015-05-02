#include "transform.h"

namespace transform
{
  
  geometries::Point translation(const geometries::Point& point, float dx, float dy)
  {

    std::vector<std::vector<float>> T = { {  1,  0, 0 },
                                          {  0,  1, 0 },
                                          { dx, dy, 1 } };

    std::vector<float> pNew = { 0, 0, 0 };

    auto P = point.get();
    for (std::size_t i = 0; i < T.size(); ++i)
    {
      for (std::size_t j = 0; j < T[i].size(); ++j)
      {
        pNew[j] += P.at(i) * T[i][j];
      }
    }

    return geometries::Point(pNew);
  }

  void translation(geometries::Geometry* geometry, float dx, float dy)
  {
    for (auto &point : geometry->getPoints())
    {
      *point = translation(*point, dx, dy);
    }
  }

  geometries::Point scaling(const geometries::Point& point, float sx, float sy)
  {
    std::vector<std::vector<float>> T = { { sx,  0, 0 },
                                          {  0, sy, 0 },
                                          {  0,  0, 1 } };

    std::vector<float> pNew = { 0, 0, 0 };

    auto P = point.get();
    for (std::size_t i = 0; i < T.size(); ++i)
    {
      for (std::size_t j = 0; j < T[i].size(); ++j)
      {
        pNew[j] += P.at(i) * T[i][j];
      }
    }

    return pNew;
  }

  void scaling(geometries::Geometry* geometry, float sx, float sy)
  {    
    auto centerGeometry = geometry->center();
    auto dx = centerGeometry.getX();
    auto dy = centerGeometry.getY();

    translation(geometry, -dx, -dy); // translate to center by center Geometry
        
    for (auto point : geometry->getPoints())
    {
      *point = scaling(*point, sx, sy);
    }

    translation(geometry, dx, dy); // return to original center Geometry
  }

  geometries::Point rotate(const geometries::Point& point, float angle)
  {
    std::vector<std::vector<float>> T = { { std::cos(angle), -std::sin(angle), 0 },
                                          { std::sin(angle),  std::cos(angle), 0 },
                                          {               0,                0, 1 } };

    std::vector<float> pNew = { 0, 0, 0 };

    auto P = point.get();
    for (std::size_t i = 0; i < T.size(); ++i)
    {
      for (std::size_t j = 0; j < T[i].size(); ++j)
      {
        pNew[j] += P.at(i) * T[i][j];
      }
    }

    return pNew;
  }

}
