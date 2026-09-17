//* This file is part of OpenPronghorn.
//* https://github.com/idaholab/open_pronghorn
//*
//* Licensed under LGPL 2.1, please see LICENSE for details

#pragma once

#include "AuxKernel.h"
#include "MoltenSaltCorrosionData.h"
#include "MoltenSaltCorrosionModel.h"

/**
 * Converts an accumulated corrosion or deposition depth to areal mass loss or gain.
 */
class MoltenSaltMassChangeAux : public AuxKernel
{
public:
  static InputParameters validParams();

  MoltenSaltMassChangeAux(const InputParameters & parameters);

protected:
  Real computeValue() override;

  const bool _mass_loss;
  const VariableValue & _depth;
  Corrosion::MoltenSaltCorrosionDatabase _database;
  Corrosion::MoltenSaltCorrosionModel _model;
  Corrosion::CorrosionFeatures _features;
};
