#ifndef _INCLUDED_TRANSFORM_
#define _INCLUDED_TRANSFORM_

#include <vector>

namespace transform
{
  std::vector<float> translation(const std::vector<float>& point, float dx, float dy)
  {    
    std::vector<std::vector<float>> T = { { 1, 0, 0 },
                                          { 0,  1, 0},
                                          {dx, dy, 1} };

    std::vector<float> pNew = {0, 0, 0};

    for (std::size_t i = 0; i < T.size(); ++i)
    {
      for (std::size_t j = 0; j < T[i].size(); ++j)
      {
        pNew[j] += point.at(i) * T[i][j];
      }
    }

    return pNew;
  }
}

#endif
