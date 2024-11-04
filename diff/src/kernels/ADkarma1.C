#include "ADkarma1.h"

registerMooseObject("diffApp", ADkarma1);

InputParameters
ADkarma1::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Anisotropic gradient Krama");
  params.addParam<MaterialPropertyName>("eps_name", "eps", "The anisotropic interface parameter");
  params.addParam<MaterialPropertyName>(
      "deps_name",
      "deps",
      "The derivative of the anisotropic interface parameter with respect to angle");
  return params;
}

ADkarma1::ADkarma1(const InputParameters & parameters)
  : ADKernelGrad(parameters),
    _eps(getADMaterialProperty<Real>("eps_name")),
    _deps(getADMaterialProperty<Real>("deps_name"))
{
}

ADRealGradient
ADkarma1::precomputeQpResidual()
{
  // Set modified gradient vector
  const ADRealGradient v(-_grad_u[_qp](1), _grad_u[_qp](0), 0);

  // Define anisotropic interface residual
  return _eps[_qp] * _deps[_qp]  * v + _eps[_qp] * _eps[_qp]  * _grad_u[_qp];
}