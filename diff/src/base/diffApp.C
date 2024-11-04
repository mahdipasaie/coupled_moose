#include "diffApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
diffApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy material output, i.e., output properties on INITIAL as well as TIMESTEP_END
  params.set<bool>("use_legacy_material_output") = false;

  return params;
}

diffApp::diffApp(InputParameters parameters) : MooseApp(parameters)
{
  diffApp::registerAll(_factory, _action_factory, _syntax);
}

diffApp::~diffApp() {}

void
diffApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"diffApp"});
  Registry::registerActionsTo(af, {"diffApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
diffApp::registerApps()
{
  registerApp(diffApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
diffApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  diffApp::registerAll(f, af, s);
}
extern "C" void
diffApp__registerApps()
{
  diffApp::registerApps();
}
