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
   bool loop();
   bool run() override;
   bool update() override;
   bool handle_events() override ;

 
  void getWindowSize();
  virtual  bool draw_lines( std::vector<Yancey_Vector> points, Yancey_Color color );  
  static uint32_t frame_expired(uint32_t interval, void *param);
  
  void set_render_color(Yancey_Color color);
  void render_clear(Yancey_Color color);
  
  void render_present();



  
  SDL_TimerID frame_timer;
    static Yancey_Frame_Counter frames;
  
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_GLContext gl_context;
  
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Color render_color;













  
};
