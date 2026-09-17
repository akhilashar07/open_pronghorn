# MoltenSaltCrReleaseAux

!syntax description /AuxKernels/MoltenSaltCrReleaseAux

This elemental diagnostic converts accumulated areal alloy mass loss to chromium-specific released
mass:

\[
m_{\mathrm{Cr,released}} = w_{\mathrm{Cr}} m_{\mathrm{alloy,lost}}.
\]

The chromium weight fraction for `material_class` comes from the corrosion database's engineering
material-property table. This relation follows the chromium-release accounting discussed in the
validation paper and its material property table (Table A.9).

```
[AuxKernels]
  [cr_release]
    type = MoltenSaltCrReleaseAux
    variable = cr_released_mg_cm2
    mass_loss = mass_loss_mg_cm2
    material_class = hastelloy_n
  []
[]
```

The output and coupled `mass_loss` variables must be elemental. Standard variable coupling ensures
the mass-loss diagnostic executes before this object at each execution point.

This diagnostic is distinct from the lumped, family-dependent salt-inventory closure
\(C_{\mathrm{Cr}} = K_{\mathrm{ppm}}(F) x_{\mathrm{corr}} (w_{\mathrm{Cr}}/0.07)\). That empirical
closure is implemented separately by `MoltenSaltCorrosionModel::saltCrPpmBase()` and is not computed
by this AuxKernel.

!syntax parameters /AuxKernels/MoltenSaltCrReleaseAux

!syntax inputs /AuxKernels/MoltenSaltCrReleaseAux

!syntax children /AuxKernels/MoltenSaltCrReleaseAux
