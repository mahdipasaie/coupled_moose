//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "diffTestApp.h"
#include "diffApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
diffTestApp::validParams()
{
  InputParameters params = diffApp::validParams();
  return params;
}

diffTestApp::diffTestApp(InputParameters parameters) : MooseApp(parameters)
{
  diffTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

diffTestApp::~diffTestApp() {}

void
diffTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  diffApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"diffTestApp"});
    Registry::registerActionsTo(af, {"diffTestApp"});
  }
}

void
diffTestApp::registerApps()
{
  registerApp(diffApp);
  registerApp(diffTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
diffTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  diffTestApp::registerAll(f, af, s);
}
extern "C" void
diffTestApp__registerApps()
{
  diffTestApp::registerApps();
}
