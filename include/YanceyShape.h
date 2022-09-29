#pragma once
#include <vector>
#include <math.h>
#include "YanceyVector.h"
//#define
//
class Yancey_shape2d{
public:
  static constexpr double Y2PI = ( 4.0f * (acos(0.0f)) );
  Yancey_shape2d();
  Yancey_shape2d(const Yancey_shape2d &s);
  virtual ~Yancey_shape2d();
  Yancey_shape2d(int id, bool solid, int sides, int radius, Yancey_Vector location);
  virtual std::vector<Yancey_Vector> get_polygon() const;
  bool collides_with(Yancey_shape2d &other);
  int id;
  bool solid;
  int sides;
  int radius;
  Yancey_Vector location;  
};
class Yancey_rect: public Yancey_shape2d{
public:
  Yancey_rect();
  virtual ~Yancey_rect();
  Yancey_rect( int id, bool solid, Yancey_Vector size, Yancey_Vector location);
  std::vector<Yancey_Vector> get_polygon() const override;
  Yancey_Vector size;
};

class Yancey_circ : public Yancey_shape2d{
public:
  Yancey_circ();
  virtual ~Yancey_circ();
  Yancey_circ( int id, bool solid,  int radius, Yancey_Vector location);
  std::vector<Yancey_Vector> get_polygon() const override;
};

