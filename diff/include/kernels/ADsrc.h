#pragma once
#include "ADKernelValue.h"

/**
 * Implements a source term for a PDE with a coupled variable U and a coefficient lambda.
 */
class ADsrc : public ADKernelValue
{
public:
  static InputParameters validParams();
  ADsrc(const InputParameters & parameters);

protected:
  /// Compute the residual
  virtual ADReal precomputeQpResidual() override;

private:
  /// Lambda coefficient for the source term
  Real _lambda;

  const ADVariableValue & _UH;
};
