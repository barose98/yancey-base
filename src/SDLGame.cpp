#include "SDLGame.h"
#include "debug_config.h"

#include <iostream>

#include <SDL_opengl.h>


SDLGame::SDLGame(const char* title, int w, int h, uint32_t framerate){
  log_func;
  this->title = title;
  this->wind_w = w;
  this->wind_h = h;
  SDLGame::frames.framerate =framerate;
  this->frame_timer = SDL_AddTimer((1000/framerate), SDLGame::frame_expired, this);

}
SDLGame::SDLGame( uint32_t framerate){
  log_func;
  this->title = "SDL Game";
  this->wind_w = 480;
  this->wind_h = 480;
    SDLGame::frames.framerate =framerate;
  this->frame_timer = SDL_AddTimer((1000/framerate), SDLGame::frame_expired, this);

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
  SDLGame::frames.count += 1;
  SDLGame::frames.ready  = true;
      return 1000 / SDLGame::frames.framerate;

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
    this->window = SDL_CreateWindow(  this->title, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,this->wind_w, this->wind_h,  SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if( !this->window ){
	  log_i << "error:" << SDL_GetError() << std::endl ;
	  return false;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    //    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
TTF_Init();
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
    this->frames.count = 0;
  while(true){
    if(!this->update())break;
    if(!this->handle_events())break;
  }
      this->kill();
      return false;
}

bool SDLGame::run()
{
  log_func;
  this->loop();
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
bool SDLGame::draw_rectangle(Yancey_Vector tl, int w, int h)
{
  SDL_Rect rect = {int(tl.x), int(tl.y), w, h};
  uint8_t suc=SDL_RenderDrawRect(this->renderer, &rect);
  return (suc == 0);
}
    
bool SDLGame::draw_points(std::vector<Yancey_Vector> points)
{
  uint8_t suc;
  for(Yancey_Vector p : points)
    {
      //      log_i<<p.x<<','<<p.y<<std::endl;
      suc=SDL_RenderDrawPoint( this->renderer, p.x, p.y);
    }
  if(suc)
    log_i<<SDL_GetError()<<std::endl;
  return true;
}
bool SDLGame::draw_lines(std::vector<Yancey_Vector> points)
{
  
  //  log_i<< points.size() <<std::endl;
  std::vector<SDL_Point> newp = {};
  int i =0;
  for( Yancey_Vector yp : points ){
    //    log_line;
    newp.push_back(  { round(yp.x),round(yp.y) } );
    i++;
  }
  // SDL_RenderDrawPoint(
    SDL_RenderDrawLines( this->renderer, newp.data(), newp.size()  );
    return SDL_TRUE;
}

void SDLGame::getWindowSize()
{
    SDL_GetWindowSize(this->window,&this->wind_w,&this->wind_h);
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
void SDLGame::render_present(uint8_t rot)
  {
    SDL_RenderPresent(this->renderer);
  }


  
