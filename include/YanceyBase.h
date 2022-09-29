#pragma once
#include <vector>

#include <stdint.h>
#include <math.h>
#include "YanceyVector.h"
#include "YanceyShape.h"
#include "colors_config.h"


struct Yancey_Frame_Counter{
  bool ready;
  uint32_t count;
};

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
template <class ID, class CB>
struct Yancey_Timer{
  Yancey_Timer(){};
  Yancey_Timer(ID id, CB cb, uint32_t interval, void* userdata):
    id(id), callback(cb), interval(interval), userdata(userdata){};

  ID id;
  CB callback;
  uint32_t interval;
  void* userdata = nullptr;
  bool ready = false;
  uint32_t count;
};

