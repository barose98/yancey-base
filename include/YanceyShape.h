#pragma once
#include <vector>
#include <math.h>
#include "YanceyVector.h"

class Yancey_shape2d{
public:
  Yancey_shape2d();
  virtual ~Yancey_shape2d();
  Yancey_shape2d(int id, bool solid, float radius, int sides, Yancey_Vector location,  Yancey_Vector  velocity);
  bool collides_withSAT(const Yancey_shape2d &other);
  bool collides_with(const Yancey_shape2d &other);
  bool collides_with(const Yancey_Vector &point);
  virtual std::vector<Yancey_Vector> get_polygon() const;
  int id;
  bool solid;
  int sides;
  float radius;
  Yancey_Vector  location;  
  Yancey_Vector  velocity;

};
class Yancey_rect: public Yancey_shape2d{
public:
  Yancey_rect();
  virtual ~Yancey_rect();
  Yancey_rect( int id, bool solid, Yancey_Vector size, Yancey_Vector location, Yancey_Vector  velocity);
  std::vector<Yancey_Vector> get_polygon() const override;
  bool collides_with(const Yancey_rect &other);
  bool collides_with(const Yancey_Vector &point);
  //  virtual bool collides_with(const Yancey_circ &other);
  Yancey_Vector size;
};
/*
class Yancey_circ : public Yancey_shape2d{
public:
  Yancey_circ();
  virtual ~Yancey_circ();
  Yancey_circ( int id, bool solid,  int radius, Yancey_Vector location,  Yancey_Vector  velocity);
  std::vector<Yancey_Vector> get_polygon() const override;
  
  bool collides_with(const Yancey_rect &other);
  //  bool collides_with(const Yancey_circ &other);

};
*/
