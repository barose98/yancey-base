#include "PicoGame.h"
#include "WaveshareGame.h"
#include "debug_config.h"
#include "colors_config.h"
#include <iostream>
#include <chrono>
//waveshare
#include <stdlib.h> // malloc() free()

#include "Infrared.h"

WaveshareGame::WaveshareGame(int framerate){
  log_func;
  this->wind_w=LCD_1IN3.WIDTH;
  this->wind_h=LCD_1IN3.HEIGHT;
  log_i<< framerate << " frames per second." << std::endl;

}
WaveshareGame::WaveshareGame(){

}
WaveshareGame::~WaveshareGame()
{
    log_func;
    delete PicoGame::frame_timer;
}

void WaveshareGame::irq_callb(unsigned int gpio_pin, uint32_t events)
{
  log_i<<"irq "<< gpio_pin <<std::endl;
}

void WaveshareGame::kill()
{
     log_func;
// Quit
}

bool WaveshareGame::init(uint8_t scan_dir)
{
  PicoGame::init(0);
  UWORD* &BlackImage = this->waveshare_image;

    log_i <<"Initializing Waveshare Window " <<  std::endl ;
    DEV_Delay_ms(100);

    if(DEV_Module_Init()!=0){
      log_i<< "DEV ERROR" <<std::endl;
        return false;
    }
    DEV_SET_PWM(50);    
    LCD_1IN3_Init(scan_dir);
    LCD_1IN3_Clear(WHITE);
    
    UDOUBLE Imagesize = LCD_1IN3_HEIGHT*LCD_1IN3_WIDTH*2;
    
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return false;
    }

    Paint_NewImage((UBYTE *)BlackImage,LCD_1IN3.WIDTH,LCD_1IN3.HEIGHT, 0,  MAGENTA);
    Paint_SetScale(65);
    Paint_Clear(BLUE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(RED);
    DEV_Delay_ms(2000);
    LCD_1IN3_Display(BlackImage);
    
    SET_Infrared_PIN(WaveshareGame::KEY_A);    
    SET_Infrared_PIN(WaveshareGame::KEY_B);
    SET_Infrared_PIN(WaveshareGame::KEY_X);
    SET_Infrared_PIN(WaveshareGame::KEY_Y);
		 
    SET_Infrared_PIN(WaveshareGame::UP);
    SET_Infrared_PIN(WaveshareGame::DOWN);
    SET_Infrared_PIN(WaveshareGame::LEFT);
    SET_Infrared_PIN(WaveshareGame::RIGHT);
    SET_Infrared_PIN(WaveshareGame::CTRL);

      this->init_interrupts();
      
    log_i <<"Initialized Waveshare."<< std::endl ;
    return true;
  
}
void WaveshareGame::init_interrupts()
{

    gpio_set_irq_enabled_with_callback (WaveshareGame::KEY_A, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
    gpio_set_irq_enabled_with_callback (WaveshareGame::KEY_B, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
    gpio_set_irq_enabled_with_callback (WaveshareGame::KEY_X, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
    gpio_set_irq_enabled_with_callback (WaveshareGame::KEY_Y, GPIO_IRQ_EDGE_FALL, true, WaveshareGame::irq_callb);
    
}

bool WaveshareGame::loop()
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

bool WaveshareGame::run()
{
  log_func;
  this->loop()
  return false;
}

bool WaveshareGame::handle_events()
{
  

  return true;
}

bool WaveshareGame::update(){

  return true;
}

bool WaveshareGame::draw_lines(std::vector<Yancey_Vector> points, Yancey_Color color )
{
  /*
WAVESHARE Drawing
void Paint_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void Paint_DrawLine(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color, DOT_PIXEL Line_width, LINE_STYLE Line_Style);
void Paint_DrawRectangle(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);
void Paint_DrawCircle(UWORD X_Center, UWORD Y_Center, UWORD Radius, UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);

   */
  
  int i =0;
  for( auto it = points.begin(); it < points.end() - 1; it++ ){
  //log_i<< x <<','<< y <<std::endl;
    Yancey_Vector yp = *(it);
    Yancey_Vector n = *(it+1);
    //Paint_DrawPoint((UWORD)yp.x,(UWORD)yp.y, color.make_rgb565(), DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
    Paint_DrawLine((UWORD)yp.x, (UWORD)yp.y, (UWORD)n.x, (UWORD)n.y, color.make_rgb565(),DOT_PIXEL_DFT ,LINE_STYLE_SOLID);
    i++;
    }
  
  return true;
}

void WaveshareGame::getWindowSize()
{
  this->wind_w=LCD_1IN3.WIDTH;
  this->wind_h=LCD_1IN3.HEIGHT;
}

  void WaveshareGame::set_render_color(Yancey_Color color)
  {
    this->render_color = color;

  }

  void WaveshareGame::render_clear(Yancey_Color color)
  {
    this->set_render_color(color);
    Paint_Clear(color.make_rgb565());
  }

void WaveshareGame::render_present(uint8_t rot)
  {
    Paint_SetRotate(UWORD(rot));
    LCD_1IN3_Display(this->waveshare_image);
  }
  void WaveshareGame::rotate_image(uint8_t rot)
  {
    Paint_SetRotate(UWORD(rot));
  }

  void WaveshareGame::draw_num(Yancey_Vector tl, uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg)
  {
    Paint_DrawNum(UWORD(tl.x), UWORD(tl.y), num, &Font20, places,  fg.make_rgb565(),  bg.make_rgb565());

  }
  void WaveshareGame::draw_string(Yancey_Vector tl, const char* str, Yancey_Color fg, Yancey_Color bg)
  {
    // fg & bg switched.
    Paint_DrawString_EN(UWORD(tl.x), UWORD(tl.y), str, &Font20, bg.make_rgb565(),  fg.make_rgb565());
    //    Paint_DrawString_EN(UWORD(tl.x), UWORD(tl.y), str, &Font20, WHITE, WHITE);
  }
