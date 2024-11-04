#include "ADTimeop.h"

registerMooseObject("diffApp", ADTimeop);

InputParameters
ADTimeop::validParams()
{
    InputParameters params = ADTimeKernelValue::validParams();
    params.addClassDescription("Implements the time derivative term with anisotropy a(theta)^2 and coefficient tau_0.");
    params.addParam<Real>("tau0", 1.0, "Coefficient tau_0 for the time derivative term.");
    params.addParam<MaterialPropertyName>("eps_name", "eps", "The anisotropic interface parameter");
    return params;
}

ADTimeop::ADTimeop(const InputParameters & parameters)
  : ADTimeKernelValue(parameters),
    _tau0(getParam<Real>("tau0")),
    _eps(getADMaterialProperty<Real>("eps_name"))
{
}

ADReal
ADTimeop::precomputeQpResidual()
{
    // Compute the time derivative term: tau_0 * a(theta)^2 * d(phi)/dt
    return _tau0 * _eps[_qp]* _eps[_qp]* _u_dot[_qp];
}