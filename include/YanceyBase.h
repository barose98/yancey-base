#pragma once
#include <vector>

#include <math.h>
#include "YanceyVector.h"
#include "YanceyShape.h"
#include "YanceyPhysics_B2D.h"

class GameBase{
public:
  virtual bool init();
  virtual void kill();
  virtual bool load();
  virtual bool update();
  virtual bool run();  
  virtual bool handleEvents();
  
  //virtual bool draw_gl(float* points);

};

