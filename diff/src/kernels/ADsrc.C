#include "ADsrc.h"

registerMooseObject("diffApp", ADsrc);

InputParameters
ADsrc::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addParam<Real>("lambda", 3.1913, "Coefficient of the source term");  
  params.addCoupledVar("UH", "Variable U from the second equation"); 
  return params;
}

ADsrc::ADsrc(const InputParameters & parameters)
  : ADKernelValue(parameters),
    _lambda(getParam<Real>("lambda")),     
    _UH(adCoupledValue("UH"))             
{
}

ADReal
ADsrc::precomputeQpResidual()
{
  const ADReal u_val = _u[_qp];  
  const ADReal U_val = _UH[_qp]; 
  return -(u_val - _lambda * U_val * (1.0 - std::pow(u_val, 2))) * (1.0 - std::pow(u_val, 2)); // negative sign becuse LHS
}
