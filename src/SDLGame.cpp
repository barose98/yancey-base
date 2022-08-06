#include "SDLGame.h"
#include "debug_config.h"
#include "colors_config.h"
#include <iostream>
#include <chrono>
//#include 
#include <SDL_opengl.h>
//#include "GL/glew.h"
//#include "GL/glx.h"


SDLGame::SDLGame(const char* title, int w, int h){
  log_func;
  this->title = title;
  this->wind_w = w;
  this->wind_h = h;
}
SDLGame::SDLGame(){

}
SDLGame::~SDLGame()
{
    log_func;
}
void SDLGame::kill()
{
    log_i<< "Killing..." << std::endl ;
// Quit
    SDL_GL_DeleteContext(this->gl_context);  
    SDL_DestroyWindow( this->window );
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

bool SDLGame::init()
{

    log_i <<"Initializing OPENGL SDL Window " <<  std::endl ;
    int val = SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    if( val < 0){
	  log_i <<"error:" << SDL_GetError() << std::endl ;
       return false;
       }
    this->window = SDL_CreateWindow(  this->title, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,this->wind_w, this->wind_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if( !this->window ){
	  log_i << "error:" << SDL_GetError() << std::endl ;
	  return false;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    //    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

    /* Creating OpenGL Context */
    this->gl_context = SDL_GL_CreateContext(window);
    
    log_i << "VERSION: " << glGetString(GL_VERSION) << std::endl ;

    //    glewExperimental = GL_TRUE;
    //        GLenum err = glewInit();
    // glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    SDL_SetRenderDrawColor(this->renderer, YANCEYCOLOR_Blue_r, YANCEYCOLOR_Blue_g, YANCEYCOLOR_Blue_b, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);

    log_i <<"Initialized SDL."<< std::endl ;
    return true;
  
}

bool SDLGame::load()
{
    return GameBase::load();
}

bool SDLGame::loop()
{
  bool contin = true;
  
  while(contin){
     auto start1 = std::chrono::steady_clock::now(); 
     contin = this->update();
     if(!this->handleEvents())return false;
     auto end1 = std::chrono::steady_clock::now();
     auto diff1 = end1 - start1;
     this->elapsed_ms = std::chrono::duration<double, std::milli> (diff1).count();
     //     log_i << "No Function Loop : " <<  << " ms\n";
  }
 return false;
 
}

bool SDLGame::run()
{
  log_func;
  if( !this->init())
    {
      this->kill();
      return false;
    }
  if( !this->loop())
    {
      this->kill();
      return false;
    }
  return false;
}

bool SDLGame::handleEvents()
{
   SDL_Event ev; 
   while(SDL_PollEvent(&ev) != 0)
     {
       switch (ev.type) {
          case SDL_QUIT:
	    //	     this->kill();
	     return false;
          case SDL_KEYDOWN:
	     log_i << 'k' << std::endl ;
        }
     }
  return true;
}

bool SDLGame::update(){
   SDL_GL_SwapWindow(window);

   SDL_Delay(50);
  return true;
}

bool SDLGame::draw_sdl(std::vector<Yancey_Vector> points )
{
  std::vector<SDL_Point> newp = {};
  int i =0;
  for( Yancey_Vector yp : points ){
    newp.push_back( { MKS2PX(yp.x), MKS2PX(yp.y) } );
    //    log_i<< yp.x <<','<< yp.y <<" ";
    i++;
  }
  //  log_i<<"### ";
  //  for( SDL_Point sp : newp ){
  //   log_i<< sp.x <<','<< sp.y <<" ";
  //  }
  //  log_i <<std::endl;
    SDL_RenderDrawLines( this->renderer, newp.data(), newp.size()  );
    return SDL_TRUE;
}

void SDLGame::getWindowSize()
{
    SDL_GetWindowSize(this->window,&this->wind_w,&this->wind_h);
    this->wind_size_mks = { PX2MKS(this->wind_w) ,PX2MKS(this->wind_h)} ;
    //log_i<< this->wind_w_mks <<','<< this->wind_h_mks << std::endl;
}
