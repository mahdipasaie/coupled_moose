#include "E3.h"

registerMooseObject("diffApp", E3);

InputParameters
E3::validParams()
{
    auto params = ADKernelValue::validParams();
    params.addClassDescription("Eq2 last term LHS sign negative . ");
    params.addRequiredCoupledVar("op", "Coupled variable");
    params.addParam<Real>("k", 0.15, "Coefficient tau_0 for the time derivative term.");
    return params;
}

E3::E3(const InputParameters & parameters)
  : ADKernelValue(parameters), 
  _v_dot(adCoupledDot("op")),
  _k(getParam<Real>("k"))
{
}

ADReal
E3::precomputeQpResidual()
{
    ADReal _scale = (1+(1-_k)*_u[_qp])/2;

    return -(_scale * _v_dot[_qp]);
}
