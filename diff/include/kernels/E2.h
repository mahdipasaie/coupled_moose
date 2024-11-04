#pragma once
#include "E2.h"
/**
 * This kernel implements the first 3 terms on the right side of eq. op.
 */
class E2 : public ADKernelGrad
{
public:
  static InputParameters validParams();

  E2(const InputParameters & parameters);

protected:
  ADRealGradient precomputeQpResidual() override;
  
  const ADVariableValue & _op;
  const ADVariableGradient & _grad_op;
  Real _k;
  Real _D;
  const ADVariableValue & _v_dot;

};