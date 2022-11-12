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

std::vector<std::vector<bool>> DIGITS={
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


Yancey_Digit::Yancey_Digit(uint8_t d,Yancey_Vector sz) : digit(d)
{
  this->size = sz;
  if((d < 0 || d > 9))return;
 for(int i = 0;i < DIGITS[d].size();i++)
   {
     bool illum = DIGITS[d][i];
     Yancey_Vector ssz = {sz.x,sz.y/5};
     Yancey_Vector sloc = {LOCS[i].x*sz.x,LOCS[i].y*sz.x};
     Yancey_Segment s(sloc,ssz,illum);
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



Yancey_Segment::Yancey_Segment(Yancey_Vector loc, Yancey_Vector ssz, bool illum)
{
  this->location = loc;
  this->size = ssz;
  this->illum = illum;
  //log_i<<"ill "<<this->illum<<" sloc "<<this->location<<std::endl;
}
std::vector<Yancey_Vector> Yancey_Segment::get_points()
{
  std::vector<Yancey_Vector> points = {};
  //log_i<<"sloc "<<this->location<<std::endl;
  //  log_i<<"ssz "<<this->size<<std::endl;
  points.push_back({this->size.x * .75,0});
  points.push_back({this->size.x * .5,this->size.y/2});
  points.push_back({this->size.x * -.5,this->size.y/2});
  points.push_back({this->size.x * -.75,0});

  points.push_back({this->size.x * -.5,this->size.y/-2});
  points.push_back({this->size.x * .5,this->size.y/-2});
    points.push_back({this->size.x * .75,0});
      for(Yancey_Vector &p : points){
	  if(this->rot)p = p.get_normal(true);
	p += this->location;
      
    }
  //log_l;
  return points;
}
Yancey_Segment::~Yancey_Segment(){}
Yancey_Segment::Yancey_Segment(const Yancey_Segment& s):
  illum(s.illum),rot(s.rot)
{
  this->location=s.location;
  this->size = s.size;
}
