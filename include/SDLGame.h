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

 
 protected: 
  void getWindowSize();
  virtual  bool draw_lines( std::vector<Yancey_Vector> points, Yancey_Color color );
  
  static uint32_t frame_expired(uint32_t interval, void *param);
  static bool start_timer( Yancey_Timer<SDL_TimerID, SDL_TimerCallback>* t );
  static bool restart_timer( Yancey_Timer<SDL_TimerID, SDL_TimerCallback>* t );
  uint32_t get_exec_ticks();
  
  void set_render_color(Yancey_Color color);
  void render_clear(Yancey_Color color);
  void render_present();
  
  Yancey_Timer<SDL_TimerID,SDL_TimerCallback> *frame_timer;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_GLContext gl_context;
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Vector wind_size_mks;
  Yancey_Color render_color;

};
