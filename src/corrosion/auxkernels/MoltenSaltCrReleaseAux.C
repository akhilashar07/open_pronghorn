//* This file is part of OpenPronghorn.
//* https://github.com/idaholab/open_pronghorn
//*
//* Licensed under LGPL 2.1, please see LICENSE for details

#include "MoltenSaltCrReleaseAux.h"

registerMooseObject("OpenPronghornApp", MoltenSaltCrReleaseAux);

InputParameters
MoltenSaltCrReleaseAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription(
      "Converts areal alloy mass loss to chromium-specific released mass using the alloy chromium "
      "weight fraction.");
  params.addRequiredCoupledVar("mass_loss", "Accumulated areal alloy mass loss [mg/cm^2].");
  params.addParam<DataFileName>(
      "database", "corrosion_database.json", "JSON molten-salt corrosion database.");
  params.addParam<std::string>("material_class", "generic_metal", "Alloy class.");
  return params;
}

MoltenSaltCrReleaseAux::MoltenSaltCrReleaseAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _mass_loss(coupledValue("mass_loss")),
    _database(getParam<DataFileName>("database")),
    _model(_database)
{
  if (isNodal())
    paramError("variable", "MoltenSaltCrReleaseAux requires an elemental auxiliary variable.");

  _features.material_class = getParam<std::string>("material_class");
}

Real
MoltenSaltCrReleaseAux::computeValue()
{
  return _model.crReleasedFromMassLossMgCm2(_features, _mass_loss[_qp]);
}
