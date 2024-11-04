#pragma once

#include "ADKernelValue.h"


class E3 : public ADKernelValue
{
public:
  static InputParameters validParams();

  E3(const InputParameters & parameters);

protected:
    virtual ADReal precomputeQpResidual() override;

    const ADVariableValue & _v_dot;
    Real _k; 
};
