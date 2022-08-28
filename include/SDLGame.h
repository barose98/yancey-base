#pragma once
#include "YanceyBase.h"
#include "YanceyPhysics_B2D.h"
#include <vector>
#include <SDL.h>

class SDLGame: public GameBase{
 public:
  SDLGame();
  SDLGame(const char* title, int w, int h, uint32_t interval);
   ~SDLGame();
  bool init(uint32_t flags);
   void kill() override;
   bool load() override;
   bool loop();
   bool run() override;
   bool update() override;
   bool handleEvents() override ;
  void getWindowSize();
  virtual  bool draw( std::vector<Yancey_Vector> points );
  
 protected:
  static uint32_t frame_expired(uint32_t interval, void *param);
  static bool start_timer( Yancey_Timer<SDL_TimerID, SDL_TimerCallback>* t );
  static bool restart_timer( Yancey_Timer<SDL_TimerID, SDL_TimerCallback>* t );
  
  void set_render_color(Yancey_Color color);
  
  Yancey_Timer<SDL_TimerID,SDL_TimerCallback> *frame_timer;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_GLContext gl_context;
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Vector wind_size_mks;
  Yancey_Color render_color;
  double elapsed_ms;
};
