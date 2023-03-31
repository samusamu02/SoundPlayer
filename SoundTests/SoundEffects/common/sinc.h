#define _USE_MATH_DEFINES
#include <cmath>

inline double sinc(double soundData)
{
  double shiftData;
  
  if (soundData == 0.0)
  {
    shiftData = 1.0;
  }
  else
  {
    shiftData = sin(soundData) / soundData;
  }
  
  return shiftData;
}
