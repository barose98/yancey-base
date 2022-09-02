#pragma once
#include "YanceyBase.h"
#include <vector>
#include <stdint.h>
#include "LCD_1in3.h"

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

protected:
  void getWindowSize();
  virtual  bool draw_lines( std::vector<Yancey_Vector> points, Yancey_Color color );
  
  static bool frame_expired(uint32_t interval, void *param);
  static bool start_timer( Yancey_Timer<repeating_timer_t, repeating_timer_callback_t> *timer;
  static bool restart_timer( Yancey_Timer<repeating_timer_t, repeating_timer_callback_t> *timer;
  
  void set_render_color(Yancey_Color color);
  void render_clear(Yancey_Color color);
  void render_present();

  UWORD* waveshare_image;
  Yancey_Timer<repeating_timer_t, repeating_timer_callback_t> *frame_timer;

  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Color render_color;
  double elapsed_ms;
};
