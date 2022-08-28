#pragma once
#include "YanceyBase.h"
#include <vector>
#include <stdint.h>

class WaveshareGame: public GameBase{
 public:
  WaveshareGame();
  WaveshareGame(const char* title, int w, int h);
   ~WaveshareGame();
  bool init(uint32_t flags);
   void kill() override;
   bool load() override;
   bool loop();
   bool run() override;
   bool update() override;
   bool handleEvents() override ;
  void getWindowSize();
  virtual  bool draw_waveshare( std::vector<Yancey_Vector> points );
  
 protected:

  // private:
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Vector wind_size_mks;
  //  float wind_h_mks;
  double elapsed_ms;
};
