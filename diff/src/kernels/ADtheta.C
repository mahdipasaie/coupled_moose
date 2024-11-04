#include "ADtheta.h"
#include "MooseMesh.h"
#include "MathUtils.h"

registerMooseObject("diffApp", ADtheta);

InputParameters
ADtheta::validParams()
{
    InputParameters params = Material::validParams();
    params.addClassDescription("2D interfacial anisotropy");
    params.addParam<Real>(
        "epsilon", 0.02, "Strength of the anisotropy");
    params.addParam<Real>(
        "w0", 1.0, "Interface width");
    params.addRequiredCoupledVar("op", "Order parameter defining the solid phase");
    
  return params;
}

ADtheta::ADtheta(const InputParameters & parameters)
  : Material(parameters),
    _epsilon(getParam<Real>("epsilon")),
    _w0(getParam<Real>("w0")),
    _eps(declareADProperty<Real>("eps")),
    _deps(declareADProperty<Real>("deps")),
    _op(adCoupledValue("op")),
    _grad_op(adCoupledGradient("op"))
{
  // this currently only works in 2D simulations
  if (_mesh.dimension() != 2)
    mooseError("ADInterfaceOrientationMaterial requires a two-dimensional mesh.");
}


void
ADtheta::computeQpProperties()
{
    const ADReal grad_x_phi = _grad_op[_qp](0);  // ∂x φ
    const ADReal grad_y_phi = _grad_op[_qp](1);  // ∂y φ

    // Compute the magnitude of the gradient
    const ADReal grad_norm = std::sqrt(grad_x_phi * grad_x_phi + grad_y_phi * grad_y_phi);

    // Initialize theta
    ADReal theta = 0.0;

    // Avoid undefined atan2 when gradient is zero
    if (grad_norm > 1e-14) // Use a small tolerance to avoid division by zero
    {
        theta = std::atan2(grad_y_phi, grad_x_phi);
    }

    // Compute anisotropy functions
    _eps[_qp] = _w0 * (1.0 + _epsilon * std::cos(4.0 * theta));
    _deps[_qp] = _w0 * (- _epsilon * 4.0 * std::sin(4.0 * theta));
}




