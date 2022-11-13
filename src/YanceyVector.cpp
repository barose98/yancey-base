
#include "YanceyVector.h"
//

std::ostream& operator <<(std::ostream &out, const Yancey_Vector &v)
  {
    out << v.x<< ","<< v.y;
    return out;
  }

  float Yancey_Vector::get_magnitude()
  {
    return  sqrt(this->x * this->x + this->y * this->y);
  }
  
  float Yancey_Vector::get_dist(const Yancey_Vector &other)
  {
    int dx = this->x - other.x;
    int dy = this->y - other.y;
    //log_i<< dx <<' '<< dy <<std::endl;
    return sqrt( ( dx * dx ) + ( dy * dy ));
  }
  
  float Yancey_Vector::get_dot(Yancey_Vector &other)
  {
    return this->x * other.x + this->y * other.y;
  }
  
  Yancey_Vector Yancey_Vector::get_normal(bool cw)
  {
    if(cw) return {this->y * -1.0f , this->x};
    return {this->y , this->x  * -1.0f};
  }

  Yancey_Vector Yancey_Vector::get_normalized()
  {
    return *(this) * (1.0f / this->get_magnitude());
  }
  
  Yancey_Vector Yancey_Vector::operator +(const Yancey_Vector &other){
    Yancey_Vector n ;
    n.x = this->x + other.x;
    n.y = this->y + other.y;
    return n;
  }
 Yancey_Vector Yancey_Vector::operator -(const Yancey_Vector &other){
    Yancey_Vector n ;
    n.x = this->x - other.x;
    n.y = this->y - other.y;
    return n;
  }
void Yancey_Vector::operator +=(const Yancey_Vector &other)
  {    
    this->x += other.x;
    this->y += other.y;
  }
void Yancey_Vector::operator -=(const Yancey_Vector &other)
  {    
    this->x -= other.x;
    this->y -= other.y;
  }
  bool Yancey_Vector::operator >(const Yancey_Vector &other)
  {    
return this->x > other.x && this->y > other.y;
  }
  bool Yancey_Vector::operator >=(const Yancey_Vector &other)
  {    
return this->x >= other.x && this->y >= other.y;
  }
  bool Yancey_Vector::operator <(const Yancey_Vector &other)
  {    
return this->x < other.x && this->y < other.y;
  }
  bool Yancey_Vector::operator <=(const Yancey_Vector &other)
  {    
return this->x <= other.x && this->y <= other.y;
  }
  
  
Yancey_Vector Yancey_Vector::operator *(float scalar)
  {
    Yancey_Vector n ;
    n.x = this->x * scalar;
    n.y = this->y * scalar;
    return n;
  }

void Yancey_Vector::operator *=(float scalar)
  {
  this->x *= scalar;
  this->y *= scalar;
  }
Yancey_Vector Yancey_Vector::operator /(float scalar)
  {
    Yancey_Vector n ;
    n.x = this->x / scalar;
    n.y = this->y / scalar;
    return n;
  }

void Yancey_Vector::operator /=(float scalar)
  {
  this->x /= scalar;
  this->y /= scalar;
  }

