#pragma once
#include "YanceyBase.h"
#include "PicoGame.h"
#include <vector>
#include <stdint.h>
#include <pico/stdlib.h>
extern "C"{
#include "ssd1306.h"
}
  
class SSD1306Game: public PicoGame{
 public:
   SSD1306Game();
   SSD1306Game(int framerate);
   ~SSD1306Game();
   bool init(uint8_t flags) override;
   bool init(uint8_t flags,  uint16_t* &BlackImage);
   void kill() override;
   bool loop() override;
   bool run() override;
   bool update() override;
   bool handle_events();
   static void irq_callb(unsigned int gpio_pin, uint32_t events);
   virtual void init_interrupts();

  void getWindowSize() override;
  virtual  bool draw_lines( std::vector<Yancey_Vector> points, Yancey_Color color ) override;  
  virtual void draw_num(Yancey_Vector tl, uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg) override;  
  virtual void draw_string(Yancey_Vector tl, const char* str,  Yancey_Color fg, Yancey_Color bg) override;  
  

  
  void set_render_color(Yancey_Color color);
  void render_clear(Yancey_Color color);
  void rotate_image(uint8_t rot);
  void render_present(uint8_t rot);
  
    ssd1306_t ssd1306disp;
  
  static const uint8_t KEY_A = 15; 
  static const uint8_t KEY_B = 17; 
  static const uint8_t KEY_X = 19; 
  static const uint8_t KEY_Y = 21;

  static const uint8_t UP = 2;
  static const uint8_t DOWN = 18;
  static const uint8_t LEFT = 16;
  static const uint8_t RIGHT = 20;
  static const uint8_t CTRL = 3;
   


};
