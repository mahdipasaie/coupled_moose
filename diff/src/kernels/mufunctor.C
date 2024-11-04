#include "mufunctor.h"
registerMooseObject("diffApp", mufunctor);

InputParameters
mufunctor::validParams()
{
  InputParameters params = FunctorMaterial::validParams();
  params.addRequiredParam<MooseFunctorName>("op", "The order parameter  used to calculate mu");
  params.addParam<Real>("mu_liquid", 1e-3, "Viscosity in the liquid region");
  params.addClassDescription("A material used to create a temperature-dependent viscosity");
  params.addParam<MaterialPropertyName>("mu", "mu", "The dynamic viscosity dependent on op");
  params.set<ExecFlagEnum>("execute_on") = {EXEC_ALWAYS};
  return params;
}

mufunctor::mufunctor(const InputParameters & parameters)
  : FunctorMaterial(parameters),
    _op(getFunctor<ADReal>("op")),
    _mu_liquid(getParam<Real>("mu_liquid"))
{
  const std::set<ExecFlagType> clearance_schedule(_execute_enum.begin(), _execute_enum.end());

  addFunctorProperty<ADReal>(
      getParam<MaterialPropertyName>("mu"),
      [this](const auto & r, const auto & t) -> ADReal
      {
        ADReal mu_solid = 1.0e6 * _mu_liquid;  // High viscosity in solid
        ADReal op = _op(r, t);
        return ((1.0 + op) / 2.0) * mu_solid + ((1.0 - op) / 2.0) * _mu_liquid;
      },
      clearance_schedule);
}
