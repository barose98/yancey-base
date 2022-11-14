#pragma once
#include <vector>
#include <math.h>
#include "debug_config.h"
#include "YanceyVector.h"
#include "YanceyShape.h"


class Yancey_Segment : public Yancey_rect{
public:
  bool illum;
  bool rot;
  Yancey_Segment();
  Yancey_Segment(Yancey_Vector loc, Yancey_Vector sz, bool illum);
   ~Yancey_Segment();
  Yancey_Segment(const Yancey_Segment& s);
  std::vector<std::vector<Yancey_Vector>> get_points();
  void rotate();
};

class Yancey_Digit{
 public:
  uint8_t digit;
  Yancey_Vector size;
  Yancey_Vector location;
  std::vector<Yancey_Segment> segments;
  Yancey_Digit(uint8_t digit,Yancey_Vector sz);
  Yancey_Digit();
  ~Yancey_Digit();
  Yancey_Digit(const Yancey_Digit& d);
  void draw();
};
