#include "YanceyBase.h"

#include "debug_config.h"



void GameBase::draw_num(Yancey_Vector br, Yancey_Vector digitsize,  uint32_t num, uint8_t places, Yancey_Color fg, Yancey_Color bg)
{
  
  uint8_t p =0;
  do{
    	  this->set_render_color(fg);
    uint32_t d = int(num / pow(10,p)) % 10;
    //log_i<<d<<std::endl;
    Yancey_Digit yd(d,digitsize);
    yd.location = {br.x-digitsize.x*2.85*p,br.y-digitsize.y};
    //this->draw_rectangle(yd.location - Yancey_Vector({2,2}), 4,4);
    for(Yancey_Segment ys : yd.segments)
      {
	if(ys.illum)
	  {
	    std::vector<std::vector<Yancey_Vector>> p =  ys.get_points();
	    std::for_each(p.begin(),p.end(),[this,&yd](std::vector<Yancey_Vector> &vp){
						vp[0] += yd.location;
						vp[1] += yd.location;
						this->draw_lines(vp);
					      });  
	  }
      }
    
    p++;
  }while(p<places);
  //log_l;
}
