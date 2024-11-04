#pragma once

#include "ADTimeKernelValue.h"
#include "Material.h"

class E1 : public ADTimeKernelValue
{
public:
  static InputParameters validParams();

  E1(const InputParameters & parameters);

protected:
  virtual ADReal precomputeQpResidual() override;
  private:

  const Real _k;

  const ADVariableValue & _op; 


};