#include "conversions.h"
#include <iomanip>

std::string utils::convert::floatToString(float number, int precision)
{
  std::ostringstream ss;
  ss << std::setprecision(precision) << number;
  return ss.str();
}
