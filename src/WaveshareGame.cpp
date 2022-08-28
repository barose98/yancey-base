#include "WaveshareGame.h"
#include "debug_config.h"
#include "colors_config.h"
#include <iostream>
#include <chrono>
//waveshare
//#include "EPD_Test.h"
#include "LCD_1in3.h"

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
void WaveshareGame::kill()
{
     log_func;
// Quit
}

bool WaveshareGame::init(uint32_t flags)
{

    log_i <<"Initializing OPENGL Waveshare Window " <<  std::endl ;

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

bool WaveshareGame::draw_waveshare(std::vector<Yancey_Vector> points )
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

}
