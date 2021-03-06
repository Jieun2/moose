[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 6
  ny = 30
  nz = 6
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./layered_integral]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Functions]
  [./y]
    type = ParsedFunction
    value = y
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./liaux]
    type = SpatialUserObjectAux
    variable = layered_integral
    execute_on = timestep
    user_object = layered_integral
  [../]
[]

[BCs]
  [./bottom]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = 0
  [../]
  [./top]
    type = DirichletBC
    variable = u
    boundary = top
    value = 1
  [../]
[]

[UserObjects]
  [./layered_integral]
    type = LayeredIntegral
    direction = y
    num_layers = 5
    variable = u
    execute_on = residual
    sample_type = average
    average_radius = 2
  [../]
[]

[Executioner]
  type = Steady
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
  [../]
[]
