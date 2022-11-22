#include "YanceyDigit.h"
std::vector<Yancey_Vector> LOCS ={
				  {0,-2},
				  {1,-1},
				  {1,1},
				  {0,2},
				  {-1,1},
				  {-1,-1},
				  {0,0}
};
std::vector<std::vector<bool>> SEGMENTS={
				       {1,1,1,1,1,1,0},//zero
				       {0,1,1,0,0,0,0},//one
				       {1,1,0,1,1,0,1},//two
				       {1,1,1,1,0,0,1},//three
				       {0,1,1,0,0,1,1},//four
				       {1,0,1,1,0,1,1},//five
				       {1,0,1,1,1,1,1},//six
				       {1,1,1,0,0,0,0},//seven
				       {1,1,1,1,1,1,1},//eight
				       {1,1,1,1,0,1,1}//nine

};

Yancey_Digit::Yancey_Digit(uint8_t d,Yancey_Vector sz, bool fillsegs) : digit(d)
{
  this->size = sz;
  if((d < 0 || d > 9))return;
 for(int i = 0;i < SEGMENTS[d].size();i++)
   {
     bool illum = SEGMENTS[d][i];
     Yancey_Vector ssz = {sz.x,sz.y/3};
     Yancey_Vector sloc = {LOCS[i].x*sz.x,LOCS[i].y*sz.x};
     Yancey_Segment s(sloc,ssz,illum,fillsegs);
     switch(i){
     case 1:
     case 2:
     case 4:
     case 5:
       s.rot = true;
       break;
     default:
       s.rot = false;
     }
     this->segments.push_back(s);
   }

}

Yancey_Digit::~Yancey_Digit(){}
Yancey_Digit::Yancey_Digit(const Yancey_Digit &yd):
  location(yd.location),size(yd.size),segments(yd.segments){}



Yancey_Segment::Yancey_Segment(Yancey_Vector loc, Yancey_Vector ssz, bool illum, bool filled)
{
  this->location = loc;
  this->size = ssz;
  this->illum = illum;
  this->filled = filled;
  //log_i<<"ill "<<this->illum<<" sloc "<<this->location<<std::endl;
}
std::vector<std::vector<Yancey_Vector>> Yancey_Segment::get_points()
{
  std::vector<std::vector<Yancey_Vector>> points = {};
  float hy = this->size.y/2;
  float y = 0.0;
  int8_t yinc = 1;
  float xextent = this->size.x * 0.8;
  if(this->filled)
    {
  for(int x = xextent;x > (0 - xextent);x--)
    {
      Yancey_Vector p1,p2;
      if(x > xextent - hy || x < (0 - xextent)+hy){
	y += yinc;
	 p1 = {x,y};
	 p2 = {x,0- y};
      }else{
	yinc = -1;
	p1 = {x,hy};
	p2 = {x,0- hy};
      }
      if(this->rot){
	p1 = p1.get_normal(true);
	p2 = p2.get_normal(true);
      }
      p1 += this->location;
      p2 += this->location; 
      points.push_back({p1,p2});
    }//for
    }else{
    Yancey_Vector p1 = {xextent,0};
    Yancey_Vector p2 = {xextent-hy,hy};    
    Yancey_Vector p3 = {0-xextent+hy,hy};    
    Yancey_Vector p4 = p1 * -1;
    Yancey_Vector p5 = p2 * -1;
    Yancey_Vector p6 = p3 * -1;
    
      if(this->rot){
	p1 = p1.get_normal(true);
	p2 = p2.get_normal(true);
	p3 = p3.get_normal(true);
	p4 = p4.get_normal(true);
	p5 = p5.get_normal(true);
	p6 = p6.get_normal(true);
      }
      p1 += this->location;
      p2 += this->location; 
      p3 += this->location;      
      p4 += this->location;      
      p5 += this->location;      
      p6 += this->location;      
  
    points.push_back({p1,p2});
    points.push_back({p2,p3});
    points.push_back({p3,p4});
    points.push_back({p4,p5});
    points.push_back({p5,p6});
    points.push_back({p6,p1});
  
}
  //log_l;
  return points;
}
Yancey_Segment::~Yancey_Segment(){}
Yancey_Segment::Yancey_Segment(const Yancey_Segment& s):
  illum(s.illum),rot(s.rot),filled(s.filled)
{
  this->location=s.location;
  this->size = s.size;
}
