#ifndef _INCLUDED_CONVERSIONS_
#define _INCLUDED_CONVERSIONS_
#include <iostream> 
#include <string> 
#include <sstream> 

namespace utils
{
  namespace convert
  {
    template <typename T>
    std::string to_string(const T& value)
    {
      std::ostringstream s;
      s << value;
      return s.str();
    }

    std::string floatToString(float number, int precision);
  }    
}


#endif

