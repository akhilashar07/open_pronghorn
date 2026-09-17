# MoltenSaltDepositionRateAux

!syntax description /AuxKernels/MoltenSaltDepositionRateAux

This elemental diagnostic evaluates the calibrated deposition correlation with the local value of a
`temperature` functor. The surface class selects the deposition morphology (`metal`, `graphite`,
`turbulent_metal`, or `laminar_metal`). For example:

```
[AuxKernels]
  [deposition_rate]
    type = MoltenSaltDepositionRateAux
    variable = deposition_rate_um_y
    temperature = T_fluid
    salt_class = fluoride_fuel
    redox_class = purified_baseline
    position_class = cold_leg
    surface_class = metal
    flow_factor = 0.75
    delta_T_C = 50
  []
[]
```

The output variable must be elemental. Integrate this rate in time with
`VariableTimeIntegrationAux` and a seconds-to-years coefficient to obtain `deposition_depth_um`.

!syntax parameters /AuxKernels/MoltenSaltDepositionRateAux

!syntax inputs /AuxKernels/MoltenSaltDepositionRateAux

!syntax children /AuxKernels/MoltenSaltDepositionRateAux
