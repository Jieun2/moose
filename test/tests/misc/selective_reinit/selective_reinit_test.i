[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./dummy]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./constant_dummy]
    type = ConstantAux
    variable = dummy
    value = 4
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[Postprocessors]
  [./u_integral]
    type = ElementIntegralVariablePostprocessor
    variable = u
    execute_on = residual
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  [./Indicators]
    [./indicator]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]
  [./Markers]
    [./box]
      type = BoxMarker
      bottom_left = '0.2 0.2 0'
      top_right = '0.8 0.8 0'
      inside = refine
      outside = coarsen
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  show = u
  [./console]
    type = Console
    perf_log = true
    linear_residual = true
  [../]
[]

[LotsOfAuxVariables]
  [./avar]
    number = 2000
  [../]
[]
