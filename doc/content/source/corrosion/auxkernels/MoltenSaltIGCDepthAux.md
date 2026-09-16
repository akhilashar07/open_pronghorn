# MoltenSaltIGCDepthAux

!syntax description /AuxKernels/MoltenSaltIGCDepthAux

This elemental diagnostic applies the reduced-order model's calibrated IGC-depth relation to an
already accumulated uniform corrosion-depth functor. It does not multiply the current corrosion rate
by the total reactor time; the input field is expected to contain the integrated corrosion-rate
history. For example:

```
[AuxKernels]
  [igc_depth]
    type = MoltenSaltIGCDepthAux
    variable = igc_depth_um
    corrosion_depth = corrosion_depth_um
    salt_class = fluoride_fuel
    redox_class = purified_baseline
  []
[]
```

The output variable must be elemental. The named `corrosion_depth` may be any scalar functor,
including an elemental FV variable. The calibrated morphology equation and damage parameters remain
in `MoltenSaltCorrosionModel`.

!syntax parameters /AuxKernels/MoltenSaltIGCDepthAux

!syntax inputs /AuxKernels/MoltenSaltIGCDepthAux

!syntax children /AuxKernels/MoltenSaltIGCDepthAux
