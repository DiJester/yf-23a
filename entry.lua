local self_ID = "YF-23A Black Widow"
declare_plugin(self_ID,
	{
		displayName       = _("YF-23A"),                                                                                                                                                                                                                                                                                        --显示名称
		developerName     = _("SchwarzWitwe & Dylan Liu"),                                                                                                                                                                                                                                                                      --开发商名称
		installed         = true,                                                                                                                                                                                                                                                                                               --安装为真
		dirName           = current_mod_path,                                                                                                                                                                                                                                                                                   --目录名
		version           = "3.0.1",                                                                                                                                                                                                                                                                                            --版本
		state             = "installed",                                                                                                                                                                                                                                                                                        --模组状态
		info              = _(
			"The YF-23A is an American single-seat, twin-engine, supersonic stealth fighter aircraft technology demonstrator, built by Northrop/McDonnell Douglas, designed for the USAF. The design was a finalist in the USAF's Advanced Tactical Fighter (ATF) competition, battling the Lockheed YF-22 for a production contract."), --说明

		binaries          =                                                                                                                                                                                                                                                                                                     --二进制文件
		{
			'yf23a',
		},
		InputProfiles     = --输入配置文件
		{
			["YF-23A"] = current_mod_path .. '/Input/YF-23A',
		},

		Skins             = --主题内容
		{
			{
				name = _("YF-23A"),
				dir  = "Skins/1"
			},
		},

		Missions          = --任务文件
		{
			{
				name = _("YF-23A"),
				dir  = "Missions",
			},
		},
		LogBook           = --行车日志
		{
			{
				name = _("YF-23A"),
				type = "YF-23A",
			},
		},

		encyclopedia_path = current_mod_path .. '/Encyclopedia'
	})


----------------------------------------------------------------------------------------------------------------------
--mounting 3d model paths and texture paths
mount_vfs_model_path(current_mod_path .. "/Shapes")         -- External Models
mount_vfs_model_path(current_mod_path .. "/Cockpit/Shapes") -- Cockpit Models
mount_vfs_texture_path(current_mod_path .. "/Textures")     -- Cockpit Textures
mount_vfs_texture_path(current_mod_path .. "/Cockpit/Textures/Cockpit_Textures")
mount_vfs_texture_path(current_mod_path .. "/Skins/1/ME")   -- 指定路径  这个路径中有着背景 背景音乐  logo
mount_vfs_sound_path(current_mod_path .. "/Sounds")         -- Sounds
mount_vfs_liveries_path(current_mod_path .. "/Liveries")    -- Liveries
-----------------------------------------------------------------------------------------------------------------------
local cfg_path = current_mod_path .. "/FM/config.lua"
dofile(cfg_path)
YF23AFM[1]          = self_ID
YF23AFM[2]          = 'YF-23A'
YF23AFM.config_path = cfg_path
YF23AFM.old         = 6

-- local fm_path       = (current_mod_path .. "/YF-23A.lua")
-- dofile(fm_path)
-- YF23AFM.config_path = fm_path

make_flyable('YF-23A', current_mod_path .. '/Cockpit/Scripts/', YF23AFM, current_mod_path .. '/Comm/comm.lua')
--make_flyable('YF-23A', current_mod_path .. '/Cockpit/Scripts/', F_23A, current_mod_path .. '/Comm/comm.lua')
--old=4代表模组基于su33进行开发
dofile(current_mod_path .. '/YF-23A.lua') --指定外部文件
dofile(current_mod_path .. '/Views.lua')  --指定外部文件
make_view_settings('YF-23A', ViewSettings, SnapViews)
----------------------------------------------------------------------------------------------------------------------

plugin_done() --插件完成
