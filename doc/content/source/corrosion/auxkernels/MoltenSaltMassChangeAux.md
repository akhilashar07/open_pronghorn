# MoltenSaltMassChangeAux

!syntax description /AuxKernels/MoltenSaltMassChangeAux

This elemental diagnostic converts an already accumulated penetration depth to areal mass change.
It uses the density for `material_class` from the corrosion database and delegates the conversion to
`MoltenSaltCorrosionModel`. It does not perform time integration.

```
[AuxKernels]
  [mass_loss]
    type = MoltenSaltMassChangeAux
    variable = mass_loss_mg_cm2
    depth = corrosion_depth_um
    mode = mass_loss
    material_class = hastelloy_n
  []
  [mass_gain]
    type = MoltenSaltMassChangeAux
    variable = mass_gain_mg_cm2
    depth = deposition_depth_um
    mode = mass_gain
    material_class = hastelloy_n
  []
[]
```

The output and coupled `depth` variables must be elemental. Standard coupling ensures the AuxKernel
that accumulates the depth executes before this algebraic diagnostic at each execution point.

!syntax parameters /AuxKernels/MoltenSaltMassChangeAux

!syntax inputs /AuxKernels/MoltenSaltMassChangeAux

!syntax children /AuxKernels/MoltenSaltMassChangeAux
