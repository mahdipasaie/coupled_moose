#pragma once
#include "ADKernelGrad.h"
/**
 * This kernel implements the first 3 terms on the right side of eq. op.
 */
class ADkarma1 : public ADKernelGrad
{
public:
  static InputParameters validParams();

  ADkarma1(const InputParameters & parameters);

protected:
  ADRealGradient precomputeQpResidual() override;
  /// Interfacial parameter
  const ADMaterialProperty<Real> & _eps;
  /// Angular derivative of interfacial parameter
  const ADMaterialProperty<Real> & _deps;
};