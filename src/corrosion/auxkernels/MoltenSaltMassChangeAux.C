//* This file is part of OpenPronghorn.
//* https://github.com/idaholab/open_pronghorn
//*
//* Licensed under LGPL 2.1, please see LICENSE for details

#include "MoltenSaltMassChangeAux.h"

registerMooseObject("OpenPronghornApp", MoltenSaltMassChangeAux);

InputParameters
MoltenSaltMassChangeAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription(
      "Converts an accumulated corrosion or deposition depth to areal mass loss or gain.");
  MooseEnum mode("mass_loss mass_gain", "mass_loss");
  params.addParam<MooseEnum>("mode", mode, "Whether to compute areal mass loss or mass gain.");
  params.addRequiredCoupledVar("depth", "Accumulated corrosion or deposition depth [um].");
  params.addParam<DataFileName>(
      "database", "corrosion_database.json", "JSON molten-salt corrosion database.");
  params.addParam<std::string>("material_class", "generic_metal", "Alloy class.");
  return params;
}

MoltenSaltMassChangeAux::MoltenSaltMassChangeAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _mass_loss(getParam<MooseEnum>("mode") == "mass_loss"),
    _depth(coupledValue("depth")),
    _database(getParam<DataFileName>("database")),
    _model(_database)
{
  if (isNodal())
    paramError("variable", "MoltenSaltMassChangeAux requires an elemental auxiliary variable.");

  _features.material_class = getParam<std::string>("material_class");
}

Real
MoltenSaltMassChangeAux::computeValue()
{
  return _mass_loss ? _model.massLossFromCorrosionDepthUm(_features, _depth[_qp])
                    : _model.massGainFromDepositionDepthUm(_features, _depth[_qp]);
}
