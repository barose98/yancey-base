#pragma once
#include "YanceyBase.h"
#include <vector>
#include <stdint.h>
#include <pico/stdlib.h>







class  PicoGame  {

 public:


  virtual bool init(uint8_t flags);

   virtual void kill() = 0;
   virtual  bool loop() = 0;
   virtual bool run()  = 0;
   virtual bool update() = 0;




   virtual void getWindowSize() = 0;
  virtual  bool draw_lines( std::vector<Yancey_Vector> points ) = 0; 
  virtual  bool draw_pixels( std::vector<Yancey_Vector> points ) = 0; 
  virtual void draw_num(Yancey_Vector tl, uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg) = 0;
  virtual void draw_string(Yancey_Vector tl, const char* str,  Yancey_Color fg, Yancey_Color bg) = 0;
  

  
  static bool frame_expired(repeating_timer_t* t);  
  static repeating_timer_t* frame_timer;
  static Yancey_Frame_Counter frames;

  
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Color render_color;

};
