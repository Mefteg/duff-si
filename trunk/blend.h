#ifndef _BLEND_H
#define _BLEND_H
// *************Cubic blend***********************
class Blend
{
public:
  double S;
  double R;

  Blend() {}
  Blend(const double&,const double&);
  virtual ~Blend() {}

  virtual double operator()(const double&) const;
  
};

#endif