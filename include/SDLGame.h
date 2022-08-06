#pragma once
#include "YanceyBase.h"
#include <vector>
#include <SDL.h>

class SDLGame: public GameBase{
 public:
  SDLGame();
  SDLGame(const char* title, int w, int h);
   ~SDLGame();
  bool init() override;
   void kill() override;
   bool load() override;
   bool loop();
   bool run() override;
   bool update() override;
   bool handleEvents() override ;
  void getWindowSize();
  virtual  bool draw_sdl(std::vector<Yancey_Vector> points );
  
 protected:
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_GLContext gl_context;
  
  // private:
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Vector wind_size_mks;
  //  float wind_h_mks;
  double elapsed_ms;
};
