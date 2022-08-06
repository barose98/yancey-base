#include "YanceyBase.h"

#include <iostream>
#include "debug_config.h"

#include "GL/glx.h"

Yancey_shape2d::Yancey_shape2d(){};
Yancey_shape2d::~Yancey_shape2d(){};
Yancey_shape2d::Yancey_shape2d(int id, bool solid, float radius, int sides, Yancey_Vector location,  Yancey_Vector  velocity):\
  id(id), solid(solid), radius(radius), sides(sides), location(location), velocity(velocity){}
  
Yancey_rect::Yancey_rect(){};
Yancey_rect::~Yancey_rect(){};
Yancey_rect::Yancey_rect(int id, bool solid, Yancey_Vector size, Yancey_Vector location, Yancey_Vector  velocity): \
  Yancey_shape2d(id, solid, 0, 4, location, velocity)
{
  this->size = size;
  // this->radius = int( sqrt((w/2)*(w/2) + (h/2)*(h/2)) );
  //  log_i<<this->radius<<std::endl;
}

/*
Yancey_circ::Yancey_circ(){};
Yancey_circ::~Yancey_circ(){};
Yancey_circ::Yancey_circ(int id, bool solid, int radius, Yancey_Vector location, Yancey_Vector  velocity): \
Yancey_shape2d(id, solid, radius, 12, location, velocity)
{

}
*/

bool Yancey_shape2d::collides_with(const Yancey_shape2d &target)
{
  if(!target.solid)return false;
  if(this->id == target.id)return false;
  //  log_i << this->id << " >> " << target.id << std::endl;
  int distx = abs(this->location.x - target.location.x);
  int disty = abs(this->location.y - target.location.y);
  return  ( sqrt(distx*distx + disty*disty) < abs(this->radius + target.radius));

}

bool Yancey_rect::collides_with(const Yancey_Vector &point)
{
  return point.x > this->location.x && point.x < (this->location.x + this->size.x) && point.y > this->location.y && point.y < (this->location.y + this->size.y) ;
}
bool Yancey_shape2d::collides_with(const Yancey_Vector &point)
{  
  return this->location.get_dist(point) < this->radius;
}
/*
bool Yancey_circ::collides_with(const Yancey_rect &other)
{
  if(!other.solid)return false;  
  int r = this->radius;
  
   //this right other left
   int dot = ((this->location.x + r) - other.location.x) ;
   // this bottom other top
   int dot2 = ((this->location.y + r) - other.location.y) ;   
   // this left other right
   int dot3 = ( (other.location.x + other.size.x) - (this->location.x - r) )  ;
   //this top other bottom
   int dot4 = ((other.location.y + other.size.y) - (this->location.y - r) ) ;
   
   //log_i<< this->location.get_dot(other.location ) << std::endl;
   bool ret = ((dot>0 && dot3>0 && dot2>0 && dot4>0));
  
   //  log_i << dot << ',' << dot2 << ',' << dot3 << ',' << dot4 << std::endl;
  return ret;
   
}
*/

std::vector<Yancey_Vector> Yancey_shape2d::get_polygon() const
// std::vector<Yancey_Vector> Yancey_circ::get_polygon() const
{
    double pi = 2 * acos(0.0);
    std::vector<Yancey_Vector> newp = {{this->location.x,this->location.y} };

	//The way the coordinate system is, this is going clockwise.
	for(float f= 0.0f; f<(2.0*pi); f+=(2.0*pi)/this->sides)
	  {
	    float x =float(this->location.x + cosf(f)*this->radius );
	    float y =float(this->location.y + sinf(f)*this->radius) ;
	    newp.push_back( { x , y } );
	  }
	//need one more point at the origin
    	//newp.push_back( { (this->location.x + cosf(0.0f)*this->radius) , ( this->location.y ) } );
	return newp;
      }
std::vector<Yancey_Vector> Yancey_rect::get_polygon() const
 {
      double pi = 2 * acos(0.0);
    std::vector<Yancey_Vector> newp = {};

      Yancey_Vector tl= { this->location.x ,this->location.y};
      Yancey_Vector tr= { this->location.x + this->size.x ,this->location.y };
      Yancey_Vector br= { this->location.x + this->size.x ,this->location.y + this->size.y};
      Yancey_Vector bl= { this->location.x ,this->location.y + this->size.y};
      
      newp.push_back( tl );
      newp.push_back( tr );
      newp.push_back( br );
      newp.push_back( bl );
      newp.push_back( tl );

       return newp;      
}
    
bool GameBase::init(){ return true;}
void GameBase::kill(){}
bool GameBase::update() {  return true; }
bool GameBase::handleEvents(){   return true;}
bool GameBase::load() {  return true;}
bool GameBase::run() {  return true;}
