#pragma once

#include <vector>
#include <math.h>
#include "debug_config.h"
//

struct Yancey_Vector{
public:
  float x;
  float y;
  //  bool
  friend std::ostream& operator <<(std::ostream &out, const Yancey_Vector &v);

  float get_magnitude();  
  float get_dist(const Yancey_Vector &other);  
  float get_dot(Yancey_Vector &other);  
  Yancey_Vector get_normal(bool cw);
  Yancey_Vector get_normalized();
  Yancey_Vector operator +(const Yancey_Vector &other);
  Yancey_Vector operator -(const Yancey_Vector &other);
  void operator +=(const Yancey_Vector &other);
  void operator -=(const Yancey_Vector &other);
  bool operator >(const Yancey_Vector &other);
  bool operator >=(const Yancey_Vector &other);
  bool operator <(const Yancey_Vector &other);
  bool operator <=(const Yancey_Vector &other);
  Yancey_Vector operator *(float scalar);
  void operator *=(float scalar);
  Yancey_Vector operator /(float scalar);
  void operator /=(float scalar);
};
