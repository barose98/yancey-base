#include "WaveshareGame.h"
#include "debug_config.h"
#include "colors_config.h"
#include <iostream>
#include <chrono>
//waveshare
//#include "EPD_Test.h"


#include "DEV_Config.h"
#include "GUI_Paint.h"
//#include "ImageData.h"
//#include "Debug.h"
#include <stdlib.h> // malloc() free()

#include "Infrared.h"

WaveshareGame::WaveshareGame(const char* title, int w, int h){
  log_func;
  this->title = title;
  this->wind_w = w;
  this->wind_h = h;
}
WaveshareGame::WaveshareGame(){

}
WaveshareGame::~WaveshareGame()
{
    log_func;
}


bool WaveshareGame::start_timer( Yancey_Timer<repeating_timer_t, repeating_timer_callback_t>* ft)
{
  add_repeating_timer_ms(ft->interval, ft->callback, ft->userdata,&ft.id);
  return true;
}

bool WaveshareGame::restart_timer( Yancey_Timer<repeating_timer_t, repeating_timer_callback_t>* ft)
{
  cancel_repeating_timer(&ft->id);
  SDLGame::start_timer(ft);
  return true;
}

bool WaveshareGame::frame_expired(uint32_t interval, void *param)
{
  if(param)
  {
      WaveshareGame* th = (WaveshareGame*)param;
      th->frame_timer->ready  = true;
      return th->frame_timer->interval;
  }
  return interval;
}



void WaveshareGame::kill()
{
     log_func;
// Quit
}

bool WaveshareGame::init(UBYTE scan_dir)
{

    log_i <<"Initializing Waveshare Window " <<  std::endl ;
    LCD_1IN3_Init(scan_dir);
    log_i <<"Initialized Waveshare."<< std::endl ;
    return true;
  
}

bool WaveshareGame::load()
{
    return GameBase::load();
}

bool WaveshareGame::loop()
{
  bool contin = true;
  
  while(contin){
    //   auto start1 = std::chrono::steady_clock::now(); 
     contin = this->update();
     if(!this->handleEvents())return false;
     //auto end1 = std::chrono::steady_clock::now();
     //auto diff1 = end1 - start1;
     //this->elapsed_ms = std::chrono::duration<double, std::milli> (diff1).count();
     //     log_i << "No Function Loop : " <<  << " ms\n";
  }
 return false;
 
}

bool WaveshareGame::run()
{
  log_func;

  if( !this->loop())
    {
      this->kill();
      return false;
    }
  return false;
}

bool WaveshareGame::handleEvents()
{
  
  while(false)
     {

     }
  return true;
}

bool WaveshareGame::update(){

  return true;
}

bool WaveshareGame::draw_lines(std::vector<Yancey_Vector> points, Yancey_Color color )
{
  //  log_i<< points.size() <<std::endl;

  int i =0;
  for( Yancey_Vector yp : points ){

    //    log_line;

    // log_i<<  this->wind_size_mks.x <<','<<  this->wind_size_mks.y <<' ';
    // log_i<< yp.x <<','<< yp.y <<std::endl;
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
    LCD_1IN3_Clear(UWORD Color);
  }

void WaveshareGame::render_present()
  {
    LCD_1IN3_Display(this->waveshare_image);
  }
