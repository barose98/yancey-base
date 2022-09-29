#include  "YanceyBase.h"

#include <iostream>
#include "debug_config.h"


Yancey_shape2d::Yancey_shape2d(){};
Yancey_shape2d::Yancey_shape2d(const Yancey_shape2d &s):		\
  id(s.id), solid(s.solid), sides(s.sides), radius(s.radius), location(s.location) {}
Yancey_shape2d::~Yancey_shape2d(){};
Yancey_shape2d::Yancey_shape2d(int id, bool solid, int sides, int radius, Yancey_Vector location): \
  id(id), solid(solid), sides(sides), radius(radius), location(location) {}
  
Yancey_rect::Yancey_rect(){};
Yancey_rect::~Yancey_rect(){};
Yancey_rect::Yancey_rect(int id, bool solid, Yancey_Vector size, Yancey_Vector location): \
  Yancey_shape2d(id, solid, 4, 10, location)
{
  this->size = size;
  // this->radius = int( sqrt((w/2)*(w/2) + (h/2)*(h/2)) );
  //  log_i<<this->radius<<std::endl;
}

Yancey_circ::Yancey_circ(){};
Yancey_circ::~Yancey_circ(){};
Yancey_circ::Yancey_circ(int id, bool solid, int radius, Yancey_Vector location): \
  Yancey_shape2d(id, solid,  8, radius, location)
{

}

std::vector<Yancey_Vector> Yancey_circ::get_polygon() const
{
  return Yancey_shape2d::get_polygon();
}

std::vector<Yancey_Vector> Yancey_shape2d::get_polygon() const
{
  std::vector<Yancey_Vector> points = {};//{this->location.x,this->location.y} };
    
    for(float f= 0.0f; f < Yancey_shape2d::Y2PI; f+=Yancey_shape2d::Y2PI/this->sides)
	  {
	    float x =float(this->location.x + cosf(f)*this->radius );
	    float y =float(this->location.y + sinf(f)*this->radius) ;
	    points.push_back( { x , y } );
	    //	    log_i<< ( 4.0f * (acos(0.0f)) )  <<' '<< f <<' '<< x <<','<< y <<std::endl;
	  }
    

	return points;
  
}
std::vector<Yancey_Vector> Yancey_rect::get_polygon() const
 {

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
    
bool Yancey_shape2d::collides_with(Yancey_shape2d &other)
  {
    float diff_x = this->location.x - other.location.x ;
    float diff_y = this->location.y - other.location.y;
    return sqrt(diff_x * diff_x + diff_y * diff_y) < (this->radius + other.radius);
  }
