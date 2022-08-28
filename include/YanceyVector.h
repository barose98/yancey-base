#pragma once

#include <vector>
#include <math.h>
//

struct Yancey_Vector{
  float x;
  float y;
  //  bool 
  float get_magnitude()
  {
    return  sqrt(this->x * this->x + this->y * this->y);
  }
  
  float get_dist(const Yancey_Vector &other)
  {
    return sqrt( ( this->x - other.x ) * ( this->x - other.x ) + ( this->y - other.y ) * ( this->y - other.y ) );
  }
  
  float get_dot(Yancey_Vector &other)
  {
    return this->x * other.x + this->y * other.y;
  }
  
  Yancey_Vector get_normal(bool cw)
  {
    if(cw) return {this->y * -1.0f , this->x};
    return {this->y , this->x  * -1.0f};
  }
  Yancey_Vector get_normal_CW()
  {    
    return {this->y * -1.0f , this->x};
  }
    Yancey_Vector get_normal_CCW()
  {    
    return {this->y , this->x  * -1.0f};
  }
  
  Yancey_Vector get_normalized()
  {
    return *(this) * (1.0f / this->get_magnitude());
  }
  
  Yancey_Vector operator +(const Yancey_Vector other){
    Yancey_Vector n ;
    n.x = this->x + other.x;
    n.y = this->y + other.y;
    return n;
  }
    Yancey_Vector operator -(const Yancey_Vector other){
    Yancey_Vector n ;
    n.x = this->x - other.x;
    n.y = this->y - other.y;
    return n;
  }
  
  Yancey_Vector operator *(float scalar)
  {
    Yancey_Vector n ;
  n.x = this->x * scalar;
  n.y = this->y * scalar;
    return n;
  }
};
