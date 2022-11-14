#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include "YanceyVector.h"
#include "YanceyShape.h"
#include "YanceyDigit.h"
#include "colors_config.h"


struct Yancey_Frame_Counter{
  bool ready;
  uint32_t count;
  uint32_t framerate;
};

class GameBase{
public:  
  virtual bool init()=0;
  virtual void kill()=0;
  virtual bool update()=0;
  virtual bool run()=0;  
  virtual bool handle_events()=0;

  virtual  bool draw_rectangle(Yancey_Vector tl, int w, int h)=0;
  virtual  bool draw_lines( std::vector<Yancey_Vector> points )=0;  
  virtual  bool draw_points( std::vector<Yancey_Vector> points )=0;
  
  virtual  void set_render_color(Yancey_Color color)=0;
  virtual  void render_clear(Yancey_Color color)=0;
  virtual  void render_present(uint8_t rot)=0;

  virtual  void draw_num(Yancey_Vector br, Yancey_Vector size, uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg);
  virtual  void draw_string(Yancey_Vector tl, const char* str,  Yancey_Color fg, Yancey_Color bg)=0;
  
};
/*
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
 */
