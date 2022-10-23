#include "PicoGame.h"
#include "SSD1306Game.h"
#include "debug_config.h"
#include "colors_config.h"
#include <iostream>
#include <chrono>
//waveshare
#include <stdlib.h> // malloc() free()


#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define I2C_ADDR 0x3c

SSD1306Game::SSD1306Game(int framerate){
  log_func;
  // this->ssd1306disp = {}; //malloc(sizeof(ssd1306_t));
  
  log_i<< framerate << " frames per second." << std::endl;

}
SSD1306Game::SSD1306Game(){

}
SSD1306Game::~SSD1306Game()
{
    log_func;
    //free(this->ssd1306disp);
    delete PicoGame::frame_timer;
}

void SSD1306Game::irq_callb(unsigned int gpio_pin, uint32_t events)
{
  log_i<<"irq "<< gpio_pin <<std::endl;
}

void SSD1306Game::kill()
{
     log_func;
// Quit
}

bool SSD1306Game::init(uint8_t scan_dir)
{
  PicoGame::init(0);
    log_i <<"Initializing SSD1306 Window " <<  std::endl ;
    sleep_ms(100);

    i2c_init(I2C_PORT, 400000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    this->ssd1306disp.external_vcc=false;
    ssd1306_init(&this->ssd1306disp, 128, 64, I2C_ADDR, I2C_PORT);
    
    this->wind_w=this->ssd1306disp.width;
    this->wind_h=this->ssd1306disp.height;
    ssd1306_clear(&this->ssd1306disp);

      this->init_interrupts();
      
    log_i <<"Initialized SSD1306."<< std::endl ;
    return true;
  
}
void SSD1306Game::init_interrupts()
{
  /*
 
    gpio_set_irq_enabled_with_callback (SSD1306Game::KEY_A, GPIO_IRQ_EDGE_FALL, true, SSD1306Game::irq_callb);
    gpio_set_irq_enabled_with_callback (SSD1306Game::KEY_B, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
    gpio_set_irq_enabled_with_callback (WaveshareGame::KEY_X, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
    gpio_set_irq_enabled_with_callback (WaveshareGame::KEY_Y, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
       */
}

bool SSD1306Game::loop()
{
  
  bool contin = true;
    this->frames.count = 0;
  while(true){
    if(!this->update())break;
    if(!this->handle_events())break;
  }
      this->kill();
      return false;
}

bool SSD1306Game::run()
{
  log_func;
  this->loop()
  return false;
}

bool SSD1306Game::handle_events()
{
  return true;
}

bool SSD1306Game::update(){

  return true;
}

bool SSD1306Game::draw_lines(std::vector<Yancey_Vector> points, Yancey_Color color )
{
 
  int i =0;
  for( auto it = points.begin(); it < points.end() - 1 ; it++ ){
  //log_i<< x <<','<< y <<std::endl;
    Yancey_Vector yp = *(it);
    Yancey_Vector n = *(it+1);

    ssd1306_draw_line(&this->ssd1306disp, yp.x, yp.y, n.x, n.y);
    // ssd13606_draw_empty_square(&this->ssd1306disp, points[3].x, points[2].y, 4, 4);
	// ssd1306_draw_pixel(&this->ssd1306disp, yp.x, yp.y);
    i++;
     }
  
  return true;
}

void SSD1306Game::getWindowSize()
{
  this->wind_w=this->ssd1306disp.width;
  this->wind_h=this->ssd1306disp.height;
}

  void SSD1306Game::set_render_color(Yancey_Color color)
  {
    this->render_color = color;

  }

  void SSD1306Game::render_clear(Yancey_Color color)
  {
    this->set_render_color(color);
    ssd1306_clear(&this->ssd1306disp);
  }

void SSD1306Game::render_present(uint8_t rot)
  {
    ssd1306_show(&this->ssd1306disp);
  }
  void SSD1306Game::rotate_image(uint8_t rot)
  {

  }

  void SSD1306Game::draw_num(Yancey_Vector tl, uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg)
  {
    //Paint_DrawNum(UWORD(tl.x), UWORD(tl.y), num, &Font20, places,  fg.make_rgb565(),  bg.make_rgb565());

  }
  void SSD1306Game::draw_string(Yancey_Vector tl, const char* str, Yancey_Color fg, Yancey_Color bg)
  {
    // fg & bg switched.
    //Paint_DrawString_EN(UWORD(tl.x), UWORD(tl.y), str, &Font20, bg.make_rgb565(),  fg.make_rgb565());
    //    Paint_DrawString_EN(UWORD(tl.x), UWORD(tl.y), str, &Font20, WHITE, WHITE);
  }
