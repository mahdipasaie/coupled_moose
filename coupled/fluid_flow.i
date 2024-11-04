rho = 1
velocity_interp_method = 'rc'
advected_interp_method = 'average'

[GlobalParams]
  rhie_chow_user_object = 'rc'
[]

[UserObjects]
  [./rc]
    type = INSFVRhieChowInterpolator
    u = vel_x
    v = vel_y
    pressure = pressure
  [../]
[]

[Mesh]
    type = GeneratedMesh
    dim = 2
    nx = 200
    ny = 200
    xmin = 0.0
    xmax = 200.0
    ymin = 0.0
    ymax = 200.0
[]

[Variables]
  [./vel_x]
    type = INSFVVelocityVariable
  [../]
  [./vel_y]
    type = INSFVVelocityVariable
  [../]
  [./pressure]
    type = INSFVPressureVariable
  [../]
  [./lambda]
    family = SCALAR
    order = FIRST
  [../]
[]

[AuxVariables]
  [./phif]
  [../]
[]

[FunctorMaterials]
  [./dynamic_viscosity]
    type = mufunctor         
    op = phif
    mu_liquid = 22400
    mu = dynamic_viscosity
  [../]
[]

[FVKernels]
  [./mass]
    type = INSFVMassAdvection # ∇·u = 0
    variable = pressure
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    rho = ${rho}
  [../]
  [./u_time]
      type = INSFVMomentumTimeDerivative
      variable = vel_x
      rho = ${rho}
      momentum_component = 'x'
  [../]
  [./mean_zero_pressure] # ∫p dΩ = 0
    type = FVIntegralValueConstraint
    variable = pressure
    lambda = lambda
  [../]
  [./u_advection] # ρ(u·∇)u
    type = INSFVMomentumAdvection
    variable = vel_x
    velocity_interp_method = ${velocity_interp_method}
    advected_interp_method = ${advected_interp_method}
    rho = ${rho}
    momentum_component = 'x'
  [../]
  [./u_viscosity] # μ∇²u
    type = INSFVMomentumDiffusion
    variable = vel_x
    mu = dynamic_viscosity
    momentum_component = 'x'
  [../]
  [./u_pressure] # -∂p/∂x
    type = INSFVMomentumPressure
    variable = vel_x
    momentum_component = 'x'
    pressure = pressure
  [../]
  [./v_time]
      type = INSFVMomentumTimeDerivative
      variable = vel_y
      rho = ${rho}
      momentum_component = 'y'
  [../]
  [./v_advection] # ρ(u·∇)v
    type = INSFVMomentumAdvection
    variable = vel_y
    velocity_interp_method = ${velocity_interp_method}
    advected_interp_method = ${advected_interp_method}
    rho = ${rho}
    momentum_component = 'y'
  [../]
  [./v_viscosity] # μ∇²v
    type = INSFVMomentumDiffusion
    variable = vel_y
    mu = dynamic_viscosity
    momentum_component = 'y'
  [../]
  [./v_pressure] # -∂p/∂y
    type = INSFVMomentumPressure
    variable = vel_y
    momentum_component = 'y'
    pressure = pressure
  [../]
[]

[FVBCs]
    # Inlet velocity boundary condition on the left side
    [./inlet_left]
      type = INSFVInletVelocityBC
      variable = vel_x
      boundary = 'left'
      function = 1.0  # Specify the inlet velocity value in the x-direction
    [../]
  
    # Outlet zero-pressure boundary condition on the right side
    [./outlet_right]
      type = INSFVOutletPressureBC
      variable = pressure
      boundary = 'right'
      function = 0.0  # Set outlet pressure to zero
    [../]
  
    # No-slip boundary conditions for vel_x on top and bottom walls
    [./no_slip_x]
      type = INSFVNoSlipWallBC
      variable = vel_x
      boundary = 'top bottom'
      function = 0
    [../]
  
    # No-slip boundary conditions for vel_y on all walls
    [./no_slip_y]
      type = INSFVNoSlipWallBC
      variable = vel_y
      boundary = 'left right top bottom'
      function = 0
    [../]
[]
  
[Adaptivity]
    initial_steps = 1
    initial_marker = refine_region
    max_h_level = 1
    marker = err_phi
    interval = 10

    [./Markers]
        [./err_phi]
            type = ErrorFractionMarker
            coarsen = 0.3
            refine = 0.95
            indicator = ind_phi
        [../]
        [./refine_region]
                type = BoxMarker
                bottom_left = '90 90 0'  
                top_right = '110 110 0'   
                inside = refine         
                outside = do_nothing     
        [../]
    [../]
    [./Indicators]
        [./ind_phi]
            type = GradientJumpIndicator
            variable = phif
        [../]
    [../]
[]


[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu NONZERO'
  line_search = 'none'
  nl_rel_tol = 1e-8
  nl_abs_tol = 1e-10
  nl_max_its = 10
  end_time = 15
  dtmax = 2e-2
  dtmin = 1e-5
  scheme = 'bdf2'
  
  [TimeStepper]
    type = IterationAdaptiveDT
    dt = 1e-3
    optimal_iterations = 6
    growth_factor = 1.5
  [../]
[../]

[Outputs]
  [exodus]
    type = Exodus
    output_material_properties = true
    show_material_properties = 'mu'
  []
  checkpoint = true
  perf_graph = true
[]
