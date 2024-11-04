[Mesh]
    type = GeneratedMesh
    dim = 2
    nx = 25
    ny = 25
    xmin = 0.0
    xmax = 200.0
    ymin = 0.0
    ymax = 200.0
[]

[Variables]
    # Variables for the two equations
    [./phi]
        family = LAGRANGE
        order = FIRST
    [../]
  
    [./u]
        family = LAGRANGE
        order = FIRST
    [../]
[]

[AuxVariables]
    [./ut]
    [../]
    [./vt]
    [../]
[]

[Kernels]
    #phi
    [./phi_time_derivative]
        type = ADTimeop
        variable = phi
    [../]
    [./phi_terms1]
        type = ADkarma1
        variable = phi
    [../]
    [./phi_src]
        type = ADsrc
        variable = phi
        UH = u
    [../]
    # U
    [./U_time_derivative]
        type = E1
        variable = u
        op = phi
    [../]
    [./Div_term]
        type = E2
        variable = u
        op = phi
    [../]
    [./u_term_3]
        type = E3
        variable = u
        op = phi
        
    [../]
[]

[ICs]
    [./phiIC]
        type = SmoothCircleIC
        variable = phi
        x1 = 100.0
        y1 = 100.0
        radius = 8
        outvalue = -1 # liquid
        invalue = 1 # solid
    [../]
    [./uIC]
        type = SmoothCircleIC
        variable = u
        x1 = 100.0
        y1 = 100.0
        radius = 8
        outvalue = -0.55 # liquid
        invalue = -0.55 # solid
    [../]
[]

[Materials]
    [./Theta]
        type = ADtheta
        op = phi
    [../]
[]

[Adaptivity]
    initial_steps = 5
    initial_marker = refine_region
    max_h_level = 5
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
            variable = phi
        [../]
    [../]
[]

[Preconditioning]
    [./advanced_precond]
      type = SMP
      full = false
    [../]
  []

[Executioner]
    type = Transient
    solve_type = PJFNK                
    nl_abs_tol = 1e-6         
    nl_rel_tol = 1e-5                 
    l_max_its = 100                   
    nl_max_its = 50                    
    petsc_options_iname = '-ksp_type -pc_type -pc_hypre_type -ksp_gmres_restart -pc_hypre_boomeramg_strong_threshold'
    petsc_options_value = 'gmres hypre boomeramg 30 0.7'  
    dt = 0.018
    end_time = 75000
    
[]



[MultiApps]
    [./fluid]
      type = TransientMultiApp
      positions = '0 0 0'
      input_files = 'fluid_flow.i'
    [../]
[]

[Transfers]
    [./utrans]
      type = MultiAppGeometricInterpolationTransfer
      from_multi_app = fluid
      source_variable = vel_x
      variable = ut
    [../]
    [./vtrans]
        type = MultiAppGeometricInterpolationTransfer
        from_multi_app = fluid
        source_variable = vel_y
        variable = vt
    [../]
    [./Ttrans]
      type = MultiAppGeometricInterpolationTransfer
      to_multi_app = fluid
      source_variable = phi
      variable = phif 
    [../]
[]
  
[Outputs]
    [./exodus]
      type = Exodus
      interval = 100     
      file_base = simulation     
      execute_on = 'initial timestep_end' 
    [../]
    [./checkpoint]
            type = Checkpoint
            time_step_interval = 100  
            num_files = 2           
    [../]
[]