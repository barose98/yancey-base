#include  "YanceyBase.h"

#include <iostream>
#include "debug_config.h"


Yancey_shape2d::Yancey_shape2d(){};
Yancey_shape2d::Yancey_shape2d(const Yancey_shape2d &s):		\
  id(s.id), solid(s.solid), sides(s.sides), radius(s.radius), location(s.location) {}
Yancey_shape2d::~Yancey_shape2d(){};
Yancey_shape2d::Yancey_shape2d(int id, bool solid, int sides, float radius, Yancey_Vector location): \
  id(id), solid(solid), sides(sides), radius(radius), location(location) {}
  
Yancey_rect::Yancey_rect(){};
Yancey_rect::Yancey_rect(const Yancey_rect &r):
  Yancey_shape2d(r.id, r.solid, 4, 10, r.location){this->size=r.size;}
Yancey_rect::~Yancey_rect(){};
Yancey_rect::Yancey_rect(int id, bool solid, Yancey_Vector size, Yancey_Vector location): \
  Yancey_shape2d(id, solid, 4, 10, location)
{
  this->size = size;
  this->radius = sqrt((this->size.x/2)*(this->size.x/2) + (this->size.y/2)*(this->size.y/2)) ;
  // log_i<<this->radius<<std::endl;
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

      Yancey_Vector tl= { this->location.x - this->size.x ,this->location.y - this->size.y};
      Yancey_Vector tr= { this->location.x + this->size.x ,this->location.y - this->size.y};
      Yancey_Vector br= { this->location.x + this->size.x ,this->location.y + this->size.y};
      Yancey_Vector bl= { this->location.x - this->size.x,this->location.y + this->size.y};
      
      newp.push_back( tl );
      newp.push_back( tr );
      newp.push_back( br );
      newp.push_back( bl );
      newp.push_back( tl );
      //log_i
       return newp;      
}
    
bool Yancey_rect::collides_with(Yancey_rect other, Yancey_Vector &overlap)
{
    Yancey_Vector ttl = this->location - (this->size / 2);
    Yancey_Vector ttr = {this->location.x + this->size.x / 2 , this->location.y - this->size.y /2};
    Yancey_Vector tbr = this->location + (this->size / 2);
    Yancey_Vector tbl = {this->location.x - this->size.x / 2 , this->location.y + this->size.y /2};
    Yancey_Vector otl = other.location - (other.size / 2);
    Yancey_Vector otr = {other.location.x + other.size.x / 2 , other.location.y - other.size.y /2};
    Yancey_Vector obr = other.location + (other.size / 2);
    Yancey_Vector obl = {other.location.x - other.size.x / 2 , other.location.y + other.size.y /2};
    bool ret1 = (ttl < obr);
    bool ret2 = (tbr > otl);
    //bool ret3 = (ttl.y < otr.y);
    //bool ret4 = (ttr.y > obl.y);
    //  log_i<< ret1<<' '<<ret2 <<std::endl;
    overlap = ttl - obr;
    return (ret1 && ret2);
}
bool Yancey_rect::collides_with(Yancey_Vector v)
{
    Yancey_Vector tl = this->location - (this->size / 2);
    Yancey_Vector br = this->location + (this->size / 2);
    bool ret = (v.y >= tl.y && v.y <= br.y && v.x >= tl.x && v.x <= br.x) ;

    //    log_i<< ret <<std::endl;
    return ret;
}
bool Yancey_shape2d::collides_with(Yancey_Vector &other)
{
  return this->location.get_dist(other) < this->radius;
}

bool Yancey_shape2d::collides_with(Yancey_shape2d &other)
  {
    float diff_x = this->location.x - other.location.x ;
    float diff_y = this->location.y - other.location.y;
    //return sqrt(diff_x * diff_x + diff_y * diff_y) < (this->radius + other.radius);
        //log_i<< this->location.get_dist(other.location) <<" < "<< this->radius + other.radius <<std::endl;
    return this->location.get_dist(other.location) < (this->radius + other.radius);
  }
