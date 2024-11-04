#include "E1.h"

registerMooseObject("diffApp", E1);

InputParameters
E1::validParams()
{
    InputParameters params = ADTimeKernelValue::validParams();
    params.addClassDescription("Time derivative.");
    params.addParam<Real>("k", 0.15, "Coefficient tau_0 for the time derivative term.");
    params.addRequiredCoupledVar("op", "Order parameter defining the solid phase");

    return params;
}

E1::E1(const InputParameters & parameters)
  : ADTimeKernelValue(parameters),
    _k(getParam<Real>("k")),
    _op(adCoupledValue("op"))
{
}

ADReal
E1::precomputeQpResidual()
{
    const ADReal _scalar = ((1+_k)-(1-_k)*_op[_qp])/2;

    return  _scalar* _u_dot[_qp];
}