ViewSettings = {
	Cockpit = {
		[1] = {                                              -- player slot 1
			CockpitLocalPoint      = { 5.038, 1.29, 0.0 },   --cockpit model line up with external model {forward/back,up/down,left/right}
			CameraViewAngleLimits  = { 20, 140 },            -- FOV Min Max (how much zoom in/out)
			CameraAngleRestriction = { false, 90, 0.5 },
			CameraAngleLimits      = { 200, -80.000000, 110.000000 }, -- View right/left, View down/up
			limits_6DOF            = { x = { -0.050000, 0.4500000 }, y = { -0.300000, 0.100000 }, z = { -0.220000, 0.220000 }, roll = 90.000000 },
			EyePoint               = { 0.05, 0.00, 0.00 },   -- Distance from pivot point. To simulate pivot around human neck, use {0.16,0.1,0}
			ShoulderSize           = 0.2,
			Allow360rotation       = false,
		},
	},
	Chase = { -- F4 view
		LocalPoint    = { 1.6, 0.86, 0 },
		AnglesDefault = { 0.0, -15.0 },
	},
	Arcade = {
		LocalPoint    = { -20.0, 5.0, 0.0 },
		AnglesDefault = { 0.000000, -8.000000 },
	},
}

local function pilot_head_pos(tab) -- adjusts pilot view from origin of cockpit model
	if not tab then
		tab = {}
	end
	tab.viewAngle = tab.viewAngle or 75 -- initial FOV
	tab.hAngle    = tab.hAngle or 0
	tab.vAngle    = tab.vAngle or -9 -- angles down pilot view
	tab.x_trans   = tab.x_trans or 0.0 -- moves pilot view forward from x=0 (cockpit model)
	tab.y_trans   = tab.y_trans or 0.02 -- moves view up
	tab.z_trans   = tab.z_trans or 0 -- moves view right
	tab.rollAngle = tab.rollAngle or 0
	return tab
end

local function pilot2_head_pos(tab) -- backseat instructor
	if not tab then
		tab = {}
	end
	tab.viewAngle = tab.viewAngle or 75 -- initial FOV
	tab.hAngle    = tab.hAngle or 0
	tab.vAngle    = tab.vAngle or -9 -- angles down pilot view
	tab.x_trans   = tab.x_trans or 0.0 ---1.35  -- moves pilot view forward from x=0 (cockpit model)
	tab.y_trans   = tab.y_trans or 0.02 --0.375  -- moves view up
	tab.z_trans   = tab.z_trans or 0 -- moves view right
	tab.rollAngle = tab.rollAngle or 0
	return tab
end

SnapViews = {
	[1] = {                 -- player slot 1
		[1] = pilot_head_pos({}), -- num 0
		[2] = pilot_head_pos({}), --LWin + Num1 : Snap View 1
		[3] = pilot_head_pos({}),
		[4] = pilot_head_pos({}),
		[5] = pilot_head_pos({}),
		[6] = pilot_head_pos({}),
		[7] = pilot_head_pos({}),
		[8] = pilot_head_pos({}),
		[9] = pilot_head_pos({}),
		[10] = pilot_head_pos({}),
		[11] = pilot_head_pos({}), --look at left mirror
		[12] = pilot_head_pos({}), --look at right mirror
		[13] = pilot_head_pos({}), -- default view
		--[14] = pilot_head_pos({}),	-- vr view
	},
	[2] = {                 -- player slot 2
		[1] = pilot_head_pos({}), -- num 0
		[2] = pilot_head_pos({}), --LWin + Num1 : Snap View 1
		[3] = pilot_head_pos({}),
		[4] = pilot_head_pos({}),
		[5] = pilot_head_pos({}),
		[6] = pilot_head_pos({}),
		[7] = pilot_head_pos({}),
		[8] = pilot_head_pos({}),
		[9] = pilot_head_pos({}),
		[10] = pilot_head_pos({}),
		[11] = pilot_head_pos({}), --look at left mirror
		[12] = pilot_head_pos({}), --look at right mirror
		[13] = pilot_head_pos({}), -- default view	
		--[14] = pilot2_head_pos({}),	-- default view	
	},
}
