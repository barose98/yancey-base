#include "YanceyBase.h"
#include "debug_config.h"


void YanceyBase::draw_string(Yancey_Vector loc, const char* str)
{
  log_func;
}
void YanceyBase::draw_num(Yancey_Vector loc, Yancey_Vector digitsize,  uint32_t num, uint8_t places, bool fillsegs)
{  
  uint8_t p = 0;
  do{
    uint32_t d = int(num / pow(10,p)) % 10;
    //log_i<<d<<std::endl;
    Yancey_Digit yd(d,digitsize,fillsegs);
    yd.location = {loc.x-digitsize.x*2.85*p,loc.y};
    //this->draw_rectangle(yd.location - Yancey_Vector({2,2}), 4,4);
    for(Yancey_Segment ys : yd.segments)
      {
	//this->debug_loc(yd.location);
	if(ys.illum)
	  {
	    std::vector<std::vector<Yancey_Vector>> po =  ys.get_points();
	    std::for_each(po.begin(),po.end(),[this,&yd](std::vector<Yancey_Vector> &vp){
						vp[0] += yd.location;
						vp[1] += yd.location;
						this->draw_lines(vp);
					      });  
	  }
      }
    
    p++;
  }while(p < places);
  //log_l;
}
void YanceyBase::debug_loc(Yancey_Vector loc)
  {
    Yancey_Vector px = {0, loc.y};
    Yancey_Vector py = {loc.x,0};
    this->set_render_color(DEBUGCOLOR);
    this->draw_lines({px,loc,py});
  }
