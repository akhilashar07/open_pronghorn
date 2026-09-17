seconds_per_year = 31557600

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
[]

[Problem]
  solve = false
[]

[AuxVariables]
  [corrosion_rate_um_y]
    family = MONOMIAL
    order = CONSTANT
  []
  [corrosion_depth_um]
    family = MONOMIAL
    order = CONSTANT
  []
  [mass_loss_mg_cm2]
    family = MONOMIAL
    order = CONSTANT
  []
  [cr_released_mg_cm2]
    family = MONOMIAL
    order = CONSTANT
  []
  [deposition_rate_um_y]
    family = MONOMIAL
    order = CONSTANT
  []
  [deposition_depth_um]
    family = MONOMIAL
    order = CONSTANT
  []
  [mass_gain_mg_cm2]
    family = MONOMIAL
    order = CONSTANT
  []
[]

[Functions]
  [temperature]
    type = ParsedFunction
    expression = '850 + 25*t/seconds_per_year'
    symbol_names = seconds_per_year
    symbol_values = ${seconds_per_year}
  []
[]

[AuxKernels]
  [corrosion_rate]
    type = MoltenSaltCorrosionRateAux
    variable = corrosion_rate_um_y
    temperature = temperature
    material_class = hastelloy_n
    salt_class = fluoride_fuel
    redox_class = purified_baseline
    flow_factor = 0.75
    delta_T_C = 50
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [corrosion_depth]
    type = VariableTimeIntegrationAux
    variable = corrosion_depth_um
    variable_to_integrate = corrosion_rate_um_y
    coefficient = ${fparse 1 / seconds_per_year}
    order = 1
    execute_on = TIMESTEP_END
  []
  [mass_loss]
    type = MoltenSaltMassChangeAux
    variable = mass_loss_mg_cm2
    depth = corrosion_depth_um
    mode = mass_loss
    material_class = hastelloy_n
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [cr_release]
    type = MoltenSaltCrReleaseAux
    variable = cr_released_mg_cm2
    mass_loss = mass_loss_mg_cm2
    material_class = hastelloy_n
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [deposition_rate]
    type = MoltenSaltDepositionRateAux
    variable = deposition_rate_um_y
    temperature = temperature
    salt_class = fluoride_fuel
    redox_class = purified_baseline
    position_class = cold_leg
    surface_class = turbulent_metal
    flow_factor = 0.75
    delta_T_C = 50
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [deposition_depth]
    type = VariableTimeIntegrationAux
    variable = deposition_depth_um
    variable_to_integrate = deposition_rate_um_y
    coefficient = ${fparse 1 / seconds_per_year}
    order = 1
    execute_on = TIMESTEP_END
  []
  [mass_gain]
    type = MoltenSaltMassChangeAux
    variable = mass_gain_mg_cm2
    depth = deposition_depth_um
    mode = mass_gain
    material_class = hastelloy_n
    execute_on = 'INITIAL TIMESTEP_END'
  []
[]

[Postprocessors]
  [corrosion_rate]
    type = ElementAverageValue
    variable = corrosion_rate_um_y
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [corrosion_depth]
    type = ElementAverageValue
    variable = corrosion_depth_um
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [mass_loss]
    type = ElementAverageValue
    variable = mass_loss_mg_cm2
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [cr_release]
    type = ElementAverageValue
    variable = cr_released_mg_cm2
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [deposition_rate]
    type = ElementAverageValue
    variable = deposition_rate_um_y
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [deposition_depth]
    type = ElementAverageValue
    variable = deposition_depth_um
    execute_on = 'INITIAL TIMESTEP_END'
  []
  [mass_gain]
    type = ElementAverageValue
    variable = mass_gain_mg_cm2
    execute_on = 'INITIAL TIMESTEP_END'
  []
[]

[Executioner]
  type = Transient
  dt = ${seconds_per_year}
  num_steps = 3
[]

[Outputs]
  csv = true
  execute_on = 'INITIAL TIMESTEP_END'
[]
