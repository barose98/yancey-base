#include "PicoGame.h"
#include "debug_config.h"
#include "colors_config.h"
#include <iostream>
#include <chrono>
//waveshare
#include <stdlib.h> // malloc() free()

Yancey_Frame_Counter PicoGame::frames = {false,0};
repeating_timer_t*  PicoGame::frame_timer = new repeating_timer_t;

bool PicoGame::init(uint8_t flags)
{
  add_repeating_timer_ms( (1000/framerate), PicoGame::frame_expired, this, PicoGame::frame_timer);
  return true;
}

bool PicoGame::frame_expired(repeating_timer_t* t)
{
  //  log_func;
  // log_i<< (t->user_data == NULL) <<std::endl;
   if(t->user_data != NULL)
  {
    // WaveshareGame* th = (WaveshareGame*)t->user_data;
      PicoGame::frames.ready  = true;
      PicoGame::frames.count += 1;
      return true;
        }
      //  return false;
}
