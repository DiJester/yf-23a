F_23A = {

	Name                      = 'YF-23A', --AG
	DisplayName               = _('YF-23A'), --AG
	Picture                   = "YF-23A.png",
	Rate                      = "50",
	Shape                     = "YF-23A", --AG	
	WorldID                   = WSTYPE_PLACEHOLDER,
	--WorldID 		= 6,

	shape_table_data          =
	{
		{
			file        = 'YF-23A', --AG
			life        = 20,      -- lifebar
			vis         = 3,       -- visibility gain.
			desrt       = 'YF-23A-oblomok', -- Name of destroyed object file name
			fire        = { 300, 2 }, -- Fire on the ground after destoyed: 300sec 2m
			username    = 'YF-23A', --AG
			index       = WSTYPE_PLACEHOLDER,
			classname   = "lLandPlane",
			positioning = "BYNORMAL",
		},
		{
			name = "YF-23A-oblomok",
			file = "YF-23A-oblomok",
			fire = { 240, 2 },
		},
	},

	LandRWCategories          =
	{
		[1] =
		{
			Name = "AircraftCarrier",
		},
		[2] =
		{
			Name = "AircraftCarrier With Catapult",
		},
		[3] =
		{
			Name = "AircraftCarrier With Tramplin",
		},
	}, -- end of LandRWCategories
	TakeOffRWCategories       =
	{
		[1] =
		{
			Name = "AircraftCarrier",
		},
		[2] =
		{
			Name = "AircraftCarrier With Catapult",
		},
		[3] =
		{
			Name = "AircraftCarrier With Tramplin",
		},
	}, -- end of TakeOffRWCategories

	mapclasskey               = "P0091000024",
	attribute                 = { wsType_Air, wsType_Airplane, wsType_Fighter, WSTYPE_PLACEHOLDER, "Fighters", "Refuelable", }, --AG
	Categories                = { "{78EFB7A2-FD52-4b57-A6A6-3BF0E1D6555F}", "Interceptor", },

	M_empty                   = 13154, --13380,	-- kg  with pilot and nose load, F15
	M_nominal                 = 18216, -- 19000,kg (Empty Plus Full Internal Fuel)
	M_max                     = 28123, -- 30845,kg (Maximum Take Off Weight)
	M_fuel_max                = 10124, -- kg (Internal Fuel Only)
	H_max                     = 19800, -- m  (Maximum Operational Ceiling)
	average_fuel_consumption  = 0.271,
	CAS_min                   = 61, -- Minimum CAS speed (m/s) (for AI)
	V_opt                     = 486, -- Cruise speed (m/s) (for AI)
	V_take_off                = 69, -- Take off speed in m/s (for AI)
	V_land                    = 71, -- Land speed in m/s (for AI)
	has_afteburner            = true,
	has_speedbrake            = true,
	radar_can_see_ground      = true,

	nose_gear_pos             = { 4.674, -2.087, 0 },   -- nosegear coord （前后 上下 左右）
	nose_gear_wheel_diameter  = 0.513,                  -- in m

	main_gear_pos             = { -2.878, -2.163, 2.022 }, -- main gear coords
	main_gear_wheel_diameter  = 0.709,                  -- in m

	AOA_take_off              = 0.16,                   -- AoA in take off (for AI)
	stores_number             = 6,
	bank_angle_max            = 60,                     -- Max bank angle (for AI)
	Ny_min                    = -3,                     -- Min G (for AI)
	Ny_max                    = 9,                      -- Max G (for AI)
	V_max_sea_level           = 403,                    -- Max speed at sea level in m/s (for AI)
	V_max_h                   = 737.5,                  -- Max speed at max altitude in m/s (for AI)
	wing_area                 = 88,                     -- wing area in m2
	thrust_sum_max            = 23308,                  -- thrust in kgf (64.3 kN)
	thrust_sum_ab             = 32630,                  -- thrust in kgf (95.1 kN)
	Vy_max                    = 350,                    -- Max climb speed in m/s (for AI)
	flaps_maneuver            = 1,
	Mach_max                  = 2.2,                    -- Max speed in Mach (for AI)
	range                     = 4489,                   -- Max range in km (for AI)
	RCS                       = 0.0008,                 -- Radar Cross Section m2
	Ny_max_e                  = 9,                      -- Max G (for AI)
	detection_range_max       = 250,
	IR_emission_coeff         = 0.5,                    -- Normal engine -- IR_emission_coeff = 1 is Su-27 without afterburner. It is reference.
	IR_emission_coeff_ab      = 0.8,                    -- With afterburner
	tand_gear_max             = 3.73,                   --XX  1.732 FA18 3.73,
	tanker_type               = 1,                      --F14=2/S33=4/ M29=0/S27=0/F15=1/ F16=1/To=0/F18=2/A10A=1/ M29K=4/F4=0/
	wing_span                 = 13.29,                  --XX  wing spain in m
	wing_type                 = 0,                      -- 0=FIXED_WING/ 1=VARIABLE_GEOMETRY/ 2=FOLDED_WING/ 3=ARIABLE_GEOMETRY_FOLDED
	length                    = 20.55,
	height                    = 4.24,
	crew_size                 = 1, --XX
	engines_count             = 2, --XX
	wing_tip_pos              = { -3.586, 0.146, 6.769 },
	EPLRS                     = true,
	TACAN_AA                  = true,
	engines_nozzles           =
	{
		[1] =
		{
			pos                 = { -8.002, 0.452, -1.227 }, -- right engine
			elevation           = 0,                --winkel nach oben unten
			diameter            = 0.8,              --cone diameter   Kreis �
			exhaust_length_ab   = 3.356,            --lenght in m  Kreis � kegel efekt
			exhaust_length_ab_K = 0.76,
			smokiness_level     = 0.01,
		}, -- end of [1]
		[2] =
		{
			pos                 = { -8.002, 0.452, 1.227 }, --left engine
			elevation           = 0,
			diameter            = 0.8,
			exhaust_length_ab   = 3.356,
			exhaust_length_ab_K = 0.76,
			smokiness_level     = 0.01,
		}, -- end of [2]
	}, -- end of engines_nozzles
	crew_members              =
	{
		[1] =
		{
			ejection_seat_name = 58,
			pilot_name         = 19,
			drop_canopy_name   = "YF-23A-fonar",
			pos                = { 5.007, 0.165, 0 },
			canopy_pos         = { 3.533, 1.209, 0 },
		}, -- end of [1]
	}, -- end of crew_members
	brakeshute_name           = 0,
	is_tanker                 = false,
	air_refuel_receptacle_pos = { 0.724, 1.172, 0 }, --{1.512,	0.805,	0},
	fires_pos                 =
	{
		[1] = { -1.842, 0.563, 0 },
		[2] = { -1.644, 0.481, 2.87 },
		[3] = { -1.389, 0.461, -3.232 },
		[4] = { -0.82, 0.265, 2.774 },
		[5] = { -0.82, 0.265, -2.774 },
		[6] = { -0.82, 0.255, 4.274 },
		[7] = { -0.82, 0.255, -4.274 },
		[8] = { -5.753, 0.06, 0.705 },
		[9] = { -5.753, 0.06, -0.705 },
		[10] = { -0.992, 0.85, 0 },
		[11] = { -1.683, 0.507, -2.91 },
	}, -- end of fires_pos

	effects_presets           = {
		{ effect = "OVERWING_VAPOR", file = current_mod_path .. "/Effects/YF-23A_overwingVapor.lua" },
	},

	chaff_flare_dispenser     =
	{
		[1] =
		{
			dir = { 0, -1, 0 },
			pos = { 1.158, -1.77, -0.967 },
		}, -- end of [1]
		[2] =
		{
			dir = { 0, -1, 0 },
			pos = { 1.158, -1.77, 0.967 },
		}, -- end of [2]
	}, -- end of chaff_flare_dispenser

	-- Countermeasures
	passivCounterm            = {
		CMDS_Edit         = true,
		SingleChargeTotal = 180,
		chaff             = { default = 90, increment = 45, chargeSz = 1 },
		flare             = { default = 45, increment = 45, chargeSz = 2 }
	},


	CanopyGeometry     = makeAirplaneCanopyGeometry(LOOK_AVERAGE, LOOK_AVERAGE, LOOK_AVERAGE),

	Sensors            = {
		RADAR = "AN/APG-63", --F15
		RWR   = "Abstract RWR" --F15
	},
	Countermeasures    = {
		ECM = "AN/ALQ-135" --F15
	},
	Failures           = {
		{ id = 'asc',       label = _('ASC'),       enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'autopilot', label = _('AUTOPILOT'), enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'hydro',     label = _('HYDRO'),     enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'l_engine',  label = _('L-ENGINE'),  enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'r_engine',  label = _('R-ENGINE'),  enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'radar',     label = _('RADAR'),     enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		--{ id = 'eos',  		label = _('EOS'), 		enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		--{ id = 'helmet',  	label = _('HELMET'), 	enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'mlws',      label = _('MLWS'),      enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'rws',       label = _('RWS'),       enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'ecm',       label = _('ECM'),       enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'hud',       label = _('HUD'),       enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
		{ id = 'mfd',       label = _('MFD'),       enable = false, hh = 0, mm = 0, mmint = 1, prob = 100 },
	},
	HumanRadio         = {
		frequency    = 127.5, -- Radio Freq
		editable     = true,
		minFrequency = 100.000,
		maxFrequency = 156.000,
		modulation   = MODULATION_AM
	},

	Guns               = { gun_mount("M_61", { count = 480 }, { muzzle_pos = { 7.3070, 0.15, -0.526 } }) --**
		--20-mm-Gatlingkanone vom Typ M61A2, die �ber 480 Schuss Munition verf�gt
	},

	pylons_enumeration = { 1, 6, 5, 2, 3, 4 },

	Pylons             = {

		pylon(1, 1, -2.037000, -0.968000, -2.986000,
			{
				use_full_connector_position = true,
				arg                         = 310,
				arg_increment               = 1,
			},
			{
				{ CLSID = "{6CEB49FC-DED8-4DED-B053-E1F033FF72D3}", arg_increment = 0.0 }, --AIM-9M
				{ CLSID = "{5CE2FF2A-645A-4197-B48D-8720AC69394F}", arg_increment = 0.0 }, --aim 9X
			}
		),
		pylon(2, 1, -2.037000, -0.968000, -2.986000,
			{
				use_full_connector_position = true,
				arg                         = 311,
				arg_increment               = 1,
			},
			{
				{ CLSID = "{40EF17B7-F508-45de-8566-6FFECC0C1AB8}", arg_increment = 0.0 }, --AIM-120C
			}
		),
		pylon(3, 1, -2.037000, -0.968000, -2.986000,
			{
				use_full_connector_position = true,
				arg                         = 312,
				arg_increment               = 1,
			},
			{
				{ CLSID = "{40EF17B7-F508-45de-8566-6FFECC0C1AB8}", arg_increment = 0.0 }, --AIM-120C
			}
		),

		pylon(4, 1, -2.037000, -0.968000, -2.986000,
			{
				use_full_connector_position = true,
				arg                         = 314,
				arg_increment               = 1,
			},
			{
				{ CLSID = "{40EF17B7-F508-45de-8566-6FFECC0C1AB8}", arg_increment = 0.0 }, --AIM-120C
			}
		),
		pylon(5, 1, -2.037000, -0.968000, -2.986000,
			{
				use_full_connector_position = true,
				arg                         = 315,
				arg_increment               = 1,
			},
			{
				{ CLSID = "{40EF17B7-F508-45de-8566-6FFECC0C1AB8}", arg_increment = 0.0 }, --AIM-120C
			}
		),
		pylon(6, 1, -2.037000, -0.968000, -2.986000,
			{
				use_full_connector_position = true,
				arg                         = 316,
				arg_increment               = 1,
			},
			{
				{ CLSID = "{6CEB49FC-DED8-4DED-B053-E1F033FF72D3}", arg_increment = 0.0 }, --AIM-9M
				{ CLSID = "{5CE2FF2A-645A-4197-B48D-8720AC69394F}", arg_increment = 0.0 }, --aim 9X
			}
		),
	},

	Tasks              = {
		aircraft_task(CAP),
		aircraft_task(Escort),
		aircraft_task(FighterSweep),
		aircraft_task(Intercept),
		aircraft_task(Reconnaissance),
		--  	aircraft_task(GroundAttack),
		--     	aircraft_task(CAS),
		--      aircraft_task(AFAC),
		--	    aircraft_task(RunwayAttack),
		--  	aircraft_task(AntishipStrike),
	},
	DefaultTask        = aircraft_task(FighterSweep),

	SFM_Data           = {
		aerodynamics = --F15
		{
			Cy0 = 0,
			Mzalfa = 4.5, --4.335
			Mzalfadt = 0.8,
			kjx = 2.75,
			kjz = 0.00125,
			Czbe = -0.200,
			cx_gear = 0.0268,
			cx_flap = 0.06,
			cy_flap = 0.4,
			cx_brk = 0.08,
			table_data =
			{
				--M    Cx0	   Cya	  B		 B4	    Omxmax Aldop Cymax
				{ 0.0, 0.0165, 0.055, 0.198, 0.22,  0.63, 25.0, 1.6 },
				{ 0.2, 0.0165, 0.055, 0.198, 0.22,  2.79, 25.0, 1.6 },
				{ 0.4, 0.0165, 0.055, 0.198, 0.22,  4.71, 25.0, 1.6 },
				{ 0.6, 0.0175, 0.055, 0.198, 0.28,  4.71, 25.0, 1.6 },
				{ 0.7, 0.0200, 0.055, 0.198, 0.28,  4.71, 23.0, 1.46 },
				{ 0.8, 0.0200, 0.055, 0.198, 0.28,  4.71, 21.7, 1.4 },
				{ 0.9, 0.0184, 0.058, 0.198, 0.20,  4.71, 20.1, 1.3 },
				{ 1.0, 0.0180, 0.062, 0.198, 0.15,  4.71, 18.9, 1.28 },
				{ 1.1, 0.0190, 0.062, 0.201, 0.09,  4.19, 17.4, 1.1 },
				{ 1.2, 0.0210, 0.062, 0.210, 0.08,  3.32, 17.0, 1.01 },
				{ 1.3, 0.0210, 0.06,  0.235, 0.10,  2.97, 16.0, 0.97 },
				{ 1.4, 0.0205, 0.056, 0.255, 0.136, 3.30, 15.0, 0.95 },
				{ 1.6, 0.0190, 0.052, 0.305, 0.21,  3.23, 13.0, 0.90 },
				{ 1.8, 0.0186, 0.042, 0.381, 2.43,  3.32, 12.0, 0.65 },
				{ 2.0, 0.0186, 0.040, 0.506, 2.5,   3.49, 10.5, 0.45, },
				{ 2.2, 0.0186, 0.037, 0.755, 3.5,   0.87, 10.0, 0.37 },
				{ 2.5, 0.0180, 0.033, 0.755, 4.7,   0.85, 9.0,  0.30 },
				{ 3.9, 0.0220, 0.023, 0.9,   6.0,   0.84, 7.0,  0.2 },
			}, -- end of table_data
		}, -- end of aerodynamics
		engine =
		{
			Nmg        = 67.5,
			MinRUD     = 0,
			MaxRUD     = 1,
			MaksRUD    = 0.85,
			ForsRUD    = 0.91,
			typeng     = 1,
			hMaxEng    = 20,
			dcx_eng    = 0.0114,
			cemax      = 1.24,
			cefor      = 2.56,
			dpdh_m     = 2000,
			dpdh_f     = 3000,
			table_data = {
				--   M		Pmax		 Pfor
				{ 0.0, 131441, 156373 },
				{ 0.2, 123572, 148838 },
				{ 0.4, 118652, 144932 },
				{ 0.6, 116258, 144287 },
				{ 0.7, 115903, 145105 },
				{ 0.8, 116059, 146653 },
				{ 0.9, 116695, 148918 },
				{ 1.0, 117780, 151893 },
				{ 1.1, 118785, 154918 },
				{ 1.2, 119880, 158246 },
				{ 1.3, 121134, 161982 },
				{ 1.4, 122535, 166154 },
				{ 1.6, 125636, 175763 },
				{ 1.8, 128758, 186901 },
				{ 2.2, 130159, 192955 },
				{ 2.5, 130159, 192955 },
				{ 3.9, 130159, 192955 },
			}, -- end of table_data
		}, -- end of engine
	},


	--damage , index meaning see in  Scripts\Aircrafts\_Common\Damage.lua
	Damage      = {
		[0]  = { critical_damage = 5, args = { 146 } },
		[1]  = { critical_damage = 3, args = { 296 } },
		[2]  = { critical_damage = 3, args = { 297 } },
		[3]  = { critical_damage = 8, args = { 65 } },
		[4]  = { critical_damage = 2, args = { 298 } },
		[5]  = { critical_damage = 2, args = { 301 } },
		[7]  = { critical_damage = 2, args = { 249 } },
		[8]  = { critical_damage = 3, args = { 265 } },
		[9]  = { critical_damage = 3, args = { 154 } },
		[10] = { critical_damage = 3, args = { 153 } },
		[11] = { critical_damage = 1, args = { 167 } },
		[12] = { critical_damage = 1, args = { 161 } },
		[13] = { critical_damage = 2, args = { 169 } },
		[14] = { critical_damage = 2, args = { 163 } },
		[15] = { critical_damage = 2, args = { 267 } },
		[16] = { critical_damage = 2, args = { 266 } },
		[17] = { critical_damage = 2, args = { 168 } },
		[18] = { critical_damage = 2, args = { 162 } },
		[20] = { critical_damage = 2, args = { 183 } },
		[23] = { critical_damage = 5, args = { 223 } },
		[24] = { critical_damage = 5, args = { 213 } },
		[25] = { critical_damage = 2, args = { 226 } },
		[26] = { critical_damage = 2, args = { 216 } },
		[29] = { critical_damage = 5, args = { 224 }, deps_cells = { 23, 25 } },
		[30] = { critical_damage = 5, args = { 214 }, deps_cells = { 24, 26 } },
		[35] = { critical_damage = 6, args = { 225 }, deps_cells = { 23, 29, 25, 37 } },
		[36] = { critical_damage = 6, args = { 215 }, deps_cells = { 24, 30, 26, 38 } },
		[37] = { critical_damage = 2, args = { 228 } },
		[38] = { critical_damage = 2, args = { 218 } },
		[39] = { critical_damage = 2, args = { 244 }, deps_cells = { 53 } },
		[40] = { critical_damage = 2, args = { 241 }, deps_cells = { 54 } },
		[43] = { critical_damage = 2, args = { 243 }, deps_cells = { 39, 53 } },
		[44] = { critical_damage = 2, args = { 242 }, deps_cells = { 40, 54 } },
		[51] = { critical_damage = 2, args = { 240 } },
		[52] = { critical_damage = 2, args = { 238 } },
		[53] = { critical_damage = 2, args = { 248 } },
		[54] = { critical_damage = 2, args = { 247 } },
		[56] = { critical_damage = 2, args = { 158 } },
		[57] = { critical_damage = 2, args = { 157 } },
		[59] = { critical_damage = 3, args = { 148 } },
		[61] = { critical_damage = 2, args = { 147 } },
		[82] = { critical_damage = 2, args = { 152 } },
	},

	DamageParts =
	{
		[1] = "YF-23A-oblomok-wing-r", -- wing R
		[2] = "YF-23A-oblomok-wing-l", -- wing L
		--		[3] = "YF-23A-oblomok-noise", -- nose
		--		[4] = "YF-23A-oblomok-tail-r", -- tail
		--		[5] = "YF-23A-oblomok-tail-l", -- tail
	},

	-- VSN DCS World\Scripts\Aircrafts\_Common\Lights.lua

	lights_data = {
		typename = "collection",
		lights = {

			[1] = {
				typename = "collection", -- WOLALIGHT_STROBES
				lights = {
					--{typename  = "natostrobelight",	argument_1  = 199, period = 1.2, color = {0.8,0,0}, connector = "RESERV_BANO_1"},--R
					--{typename  = "natostrobelight",	argument_1  = 199, period = 1.2, color = {0.8,0,0}, connector = "RESERV1_BANO_1"},--L
					--{typename  = "natostrobelight",	argument_1  = 199, period = 1.2, color = {0.8,0,0}, connector = "RESERV2_BANO_1"},--H
					--{typename  = "natostrobelight",	argument_1  = 195, period = 1.2, color = {0.8,0,0}, connector = "WHITE_BEACON L"},--195
					--{typename  = "natostrobelight",	argument_1  = 196, period = 1.2, color = {0.8,0,0}, connector = "WHITE_BEACON R"},--196
					--{typename  = "natostrobelight",	argument_1  = 192, period = 1.2, color = {0.8,0,0}, connector = "BANO_0_BACK"},
					--{typename  = "natostrobelight",	argument_1  = 195, period = 1.2, color = {0.8,0,0}, connector = "RED_BEACON L"},
					--{typename  = "natostrobelight",	argument_1  = 196, period = 1.2, color = {0.8,0,0}, connector = "RED_BEACON R"},
				}
			},
			[2] = {
				typename = "collection",
				lights = {                                                                                                   -- 1=Landing light -- 2=Landing/Taxi light
					{ typename = "spotlight", connector = "MAIN_SPOT_PTR", argument = 209, dir_correction = { elevation = math.rad(-1) } }, --"MAIN_SPOT_PTR_02","RESERV_SPOT_PTR"
					{ typename = "spotlight", connector = "MAIN_SPOT_PTR", argument = 208, dir_correction = { elevation = math.rad(3) } }, --"MAIN_SPOT_PTR_01","RESERV_SPOT_PTR","MAIN_SPOT_PTL",
				}
			},
			[3] = {
				typename = "collection",
				lights = {
					-- Left Position Light (red)
					{ typename = "omnilight", connector = "BANO_1", color = { 0.99, 0.11, 0.3 }, pos_correction = { 0.1, 0, -0.2 }, argument = 190 },
					-- Right Position Light (green)
					{ typename = "omnilight", connector = "BANO_2", color = { 0, 0.894, 0.6 },   pos_correction = { 0.1, 0, 0.2 },  argument = 191 },
					-- Tail Position Light (white)
					{ typename = "omnilight", connector = "BANO_0", color = { 1, 1, 1 },         pos_correction = { 0, 0, 0 },      argument = 192 } }
			},
			[4] = {
				typename = "collection",              -- formation_lights_default
				lights = {
					{ typename = "argumentlight", argument = 200, }, --formation_lights_tail_1 = 200;
					{ typename = "argumentlight", argument = 201, }, --formation_lights_tail_2 = 201;
					{ typename = "argumentlight", argument = 202, }, --formation_lights_left   = 202;
					{ typename = "argumentlight", argument = 203, }, --formation_lights_right  = 203;
					{ typename = "argumentlight", argument = 88, }, --old aircraft arg
				}
			},
			--[[			
	[5] = { typename = "collection", -- strobe_lights_default
					lights = {
						{typename  = "strobelight",connector =  "RED_BEACON"  ,argument = 193, color = {0.8,0,0}},-- Arg 193, 83,
						{typename  = "strobelight",connector =  "RED_BEACON_2",argument = 194, color = {0.8,0,0}},-- (-1"RESERV_RED_BEACON")
						{typename  = "strobelight",connector =  "RED_BEACON"  ,argument =  83, color = {0.8,0,0}},-- Arg 193, 83,
							}
			},
--]]
		}
	},
}

add_aircraft(F_23A)
