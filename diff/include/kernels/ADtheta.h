#pragma once

#include "Material.h"

/**
 * Material to compute the angular orientation theta based on the order parameter gradient
 * and to apply an anisotropy function a(theta) = 1 + epsilon * cos(4 * theta).
 */
class ADtheta : public Material
{
public:
  static InputParameters validParams();

  ADtheta(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  Real _epsilon;
  Real _w0;

  ADMaterialProperty<Real> & _eps;
  ADMaterialProperty<Real> & _deps;

  const ADVariableValue & _op;
  const ADVariableGradient & _grad_op;
};