//* This file is part of OpenPronghorn.
//* https://github.com/idaholab/open_pronghorn
//*
//* Licensed under LGPL 2.1, please see LICENSE for details

#pragma once

#include "AuxKernel.h"
#include "MoltenSaltCorrosionData.h"
#include "MoltenSaltCorrosionModel.h"

/**
 * Evaluates the effective molten-salt deposition correlation using a local temperature functor.
 */
class MoltenSaltDepositionRateAux : public AuxKernel
{
public:
  static InputParameters validParams();

  MoltenSaltDepositionRateAux(const InputParameters & parameters);

protected:
  Real computeValue() override;

  const Moose::Functor<Real> & _temperature;
  Corrosion::MoltenSaltCorrosionDatabase _database;
  Corrosion::MoltenSaltCorrosionModel _model;
  Corrosion::CorrosionFeatures _features;
};
