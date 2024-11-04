#pragma once

#include "ADTimeKernelValue.h"
#include "Material.h"

class ADTimeop : public ADTimeKernelValue
{
public:
  static InputParameters validParams();

  ADTimeop(const InputParameters & parameters);

protected:
  virtual ADReal precomputeQpResidual() override;
  private:
  /// Coefficient tau_0
  const Real _tau0;
  /// Anisotropy function a(theta)
  const ADMaterialProperty<Real> & _eps;

};