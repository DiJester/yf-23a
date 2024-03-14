dofile(LockOn_Options.common_script_path .. 'tools.lua')
dofile(LockOn_Options.script_path .. 'devices.lua')

layoutGeometry = {}

attributes = {
    "support_for_cws",
}

creators = {}
creators[devices.DEMO] = { 'avLuaDevice', LockOn_Options.script_path .. 'Systems/demo.lua' }
creators[devices.RUDDER] = { 'avLuaDevice', LockOn_Options.script_path .. 'Systems/rudder.lua' }
creators[devices.RUDDER2] = { 'avLuaDevice', LockOn_Options.script_path .. 'Systems/rudder2.lua' }
---------------------------------------------
dofile(LockOn_Options.common_script_path .. "KNEEBOARD/declare_kneeboard_device_left.lua")
---------------------------------------------
