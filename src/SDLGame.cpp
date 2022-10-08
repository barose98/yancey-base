#include "SDLGame.h"
#include "debug_config.h"

#include <iostream>

#include <SDL_opengl.h>


SDLGame::SDLGame(const char* title, int w, int h, uint32_t framerate){
  log_func;
  this->title = title;
  this->wind_w = w;
  this->wind_h = h;
  this->frame_timer = SDL_AddTimer((100/framerate), SDLGame::frame_expired, this);

}
SDLGame::SDLGame(){

}
SDLGame::~SDLGame()
{
    log_func;

}
Yancey_Frame_Counter SDLGame::frames = {false,0};

uint32_t SDLGame::frame_expired(uint32_t interval, void *param)
{
  if(param)
  {
      SDLGame* th = (SDLGame*)param;
      th->frames.ready  = true;
      return th->frame_timer->interval;
  }
  return interval;
}

void SDLGame::kill()
{
     log_func;
// Quit
    SDL_GL_DeleteContext(this->gl_context);  
    SDL_DestroyWindow( this->window );
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}



bool SDLGame::init(uint32_t flags)
{
  log_i <<"Initializing OPENGL SDL Window " <<  std::endl ;
    int val = SDL_Init(flags);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    if( val < 0){
	  log_i <<"error:" << SDL_GetError() << std::endl ;
       return false;
       }
    this->window = SDL_CreateWindow(  this->title, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,this->wind_w, this->wind_h, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if( !this->window ){
	  log_i << "error:" << SDL_GetError() << std::endl ;
	  return false;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    //    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

    /* Creating OpenGL Context */
    this->gl_context = SDL_GL_CreateContext(window);
    
    //  log_i << "VERSION: " << glGetString(GL_VERSION) << std::endl ;
     this->set_render_color( YANCEYCOLOR_Red );

    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);

    log_i <<"Initialized SDL."<< std::endl ;
    return true;
  
}

bool SDLGame::loop()
{
  bool contin = true;
    this->frame_timer->count = 0;
  while(contin){
     contin = this->update();
     if(!this->handle_events())return false;
  }
 return false;
 
}

bool SDLGame::run()
{
  log_func;

  if( !this->loop())
    {
      this->kill();
      return false;
    }
  return false;
}

bool SDLGame::handle_events()
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

bool SDLGame::draw_lines(std::vector<Yancey_Vector> points, Yancey_Color color )
{
  
  //  log_i<< points.size() <<std::endl;
  std::vector<SDL_Point> newp = {};
  int i =0;
  for( Yancey_Vector yp : points ){
    //    Yancey_Vector n = MKS2PX(yp ,  this->wind_size_mks);
    //    log_line;
    newp.push_back(  { round(yp.x),round(yp.y) } );
    // log_i<<  this->wind_size_mks.x <<','<<  this->wind_size_mks.y <<' ';
    // log_i<< yp.x <<','<< yp.y <<std::endl;
    i++;
  }
    this->set_render_color(color);
    SDL_RenderDrawLines( this->renderer, newp.data(), newp.size()  );
    return SDL_TRUE;
}

void SDLGame::getWindowSize()
{
    SDL_GetWindowSize(this->window,&this->wind_w,&this->wind_h);
    //   this->wind_size_mks = PX2MKS(this->wind_w , this->wind_h)  ;
    //log_i<< this->wind_w_mks <<','<< this->wind_h_mks << std::endl;
}

  void SDLGame::set_render_color(Yancey_Color color)
  {
    this->render_color = color;
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a );
  }

  void SDLGame::render_clear(Yancey_Color color)
  {
    this->set_render_color(color);
    SDL_RenderClear(this->renderer);
  }
void SDLGame::render_present()
  {
    SDL_RenderPresent(this->renderer);
  }
