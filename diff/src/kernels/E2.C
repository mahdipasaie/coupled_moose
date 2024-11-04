#include "E2.h"

registerMooseObject("diffApp", E2);

InputParameters
E2::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("divergence term of EQ2.");
  params.addRequiredCoupledVar("op", "Order parameter defining the solid phase");
  params.addParam<Real>("k", 0.15, "Coefficient tau_0 for the time derivative term.");
  params.addParam<Real>("D", 2, "Coefficient tau_0 for the time derivative term.");

  return params;
}

E2::E2(const InputParameters & parameters)
    : ADKernelGrad(parameters),
    _op(adCoupledValue("op")),
    _grad_op(adCoupledGradient("op")),
    _k(getParam<Real>("k")),
    _D(getParam<Real>("D")),
    _v_dot(adCoupledDot("op"))

{
}

ADRealGradient
E2::precomputeQpResidual()
{

  const Real tol = 1e-10;
  ADReal q_phi = (1 - _op[_qp]) / 2;
  ADRealGradient term1 = _D * q_phi * _grad_u[_qp];
  ADReal norm_grad_phi = _grad_op[_qp].norm();
  ADReal term2 = 0.0;

  if (norm_grad_phi > tol)
  {
    term2 = 1/norm_grad_phi ;
  }

  ADRealGradient term_anti = (term1*_grad_op[_qp])*_v_dot[_qp]*(1+(1-_k)*_u[_qp])/std::pow(8,0.5);

  return term1;
}