//* This file is part of OpenPronghorn.
//* https://github.com/idaholab/open_pronghorn
//*
//* Licensed under LGPL 2.1, please see LICENSE for details

#pragma once

#include "AuxKernel.h"
#include "MoltenSaltCorrosionData.h"
#include "MoltenSaltCorrosionModel.h"

/**
 * Converts alloy mass loss to the chromium-specific released mass.
 */
class MoltenSaltCrReleaseAux : public AuxKernel
{
public:
  static InputParameters validParams();

  MoltenSaltCrReleaseAux(const InputParameters & parameters);

protected:
  Real computeValue() override;

  const VariableValue & _mass_loss;
  Corrosion::MoltenSaltCorrosionDatabase _database;
  Corrosion::MoltenSaltCorrosionModel _model;
  Corrosion::CorrosionFeatures _features;
};
