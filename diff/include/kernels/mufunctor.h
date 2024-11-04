#pragma once
#include "FunctorMaterial.h"

class mufunctor : public FunctorMaterial
{
public:
  static InputParameters validParams();  

  mufunctor(const InputParameters & parameters);  

protected:
  const Moose::Functor<ADReal> & _op; 
  const Real _mu_liquid;  
};
