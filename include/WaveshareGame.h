#pragma once
#include "YanceyBase.h"
#include <vector>
#include <stdint.h>
//#include <pico/math.h>
extern "C"{
#include "LCD_1in3.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "Infrared.h"
}
  

class WaveshareGame: public GameBase{
 public:
  WaveshareGame();
  WaveshareGame(int framerate);
   ~WaveshareGame();
  bool init(uint8_t flags);
  bool init(uint8_t flags,  UWORD* &BlackImage);
   void kill() override;
   bool load() override;
   bool loop();
   bool run() override;
   bool update() override;
   bool handleEvents() override ;
   virtual void init_interrupts();

  //protected:
  void getWindowSize();
  virtual  bool draw_lines( std::vector<Yancey_Vector> points, Yancey_Color color );  
  static bool frame_expired(repeating_timer_t* t);
  
  void set_render_color(Yancey_Color color);
  void render_clear(Yancey_Color color);
  void rotate_image(uint32_t rot);
  void render_present();
  void draw_num(Yancey_Vector tl, uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg);
  void draw_string(Yancey_Vector tl, const char* str,  Yancey_Color fg, Yancey_Color bg);
  

  UWORD* waveshare_image;
  repeating_timer_t *frame_timer;
  static Yancey_Frame_Counter frames;
  
  const char* title;
  int wind_w;
  int wind_h;
  Yancey_Color render_color;

  static const uint8_t KEY_A = 15; 
  static const uint8_t KEY_B = 17; 
  static const uint8_t KEY_X = 19; 
  static const uint8_t KEY_Y = 21;

  static const uint8_t UP = 2;
  static const uint8_t DOWN = 18;
  static const uint8_t LEFT = 16;
  static const uint8_t RIGHT = 20;
  static const uint8_t CTRL = 3;
   
  static void irq_callb(unsigned int gpio_pin, uint32_t events);

};
