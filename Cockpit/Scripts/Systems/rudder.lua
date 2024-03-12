dofile(LockOn_Options.script_path .. 'command_defs.lua')
dofile(LockOn_Options.script_path .. 'utils.lua')
dofile(LockOn_Options.script_path .. 'Systems/device_header.lua')

local dev              = GetSelf()

local update_time_step = 0.016 --update will be called 60 times per second
make_default_activity(update_time_step)

local mod_rudder        = 0
local des_rudder_ground = 0
local mod_rudder_ground = 0

local key_rudder_active = 0
local key_rudder_dir    = 0

local input_rudder      = 0

local auth_rudder       = 1

dev:listen_command(Keys.PlaneYawAxis)
dev:listen_command(Keys.LeftRudderStart)
dev:listen_command(Keys.LeftRudderStop)
dev:listen_command(Keys.RightRudderStart)
dev:listen_command(Keys.RightRudderStop)



function update()
	--get_base_sensor_data()

	rudder()
end

function post_initialize()
	print_message_to_user("Init - rudder")
end

function SetCommand(command, value)
	if command == Keys.PlaneYawAxis then
		key_rudder_active = 0
		if Sensor_Data_Mod.nose_wow == 1 then
			input_rudder      = value
			des_rudder_ground = round(value, 2)
		else
			input_rudder = value
			des_rudder_ground = 0
		end
	elseif command == Keys.LeftRudderStart then
		key_rudder_dir = -0.01
		input_rudder = -1
	elseif command == Keys.RightRudderStart then
		key_rudder_dir = 0.01
		input_rudder = 1
	elseif command == Keys.RightRudderStop or command == Keys.LeftRudderStop then
		key_rudder_dir = 0
		key_rudder_active = 1
		input_rudder = 0
	end
end

function rudder()
	if (des_rudder_ground > 0.99 or des_rudder_ground < -0.99) and key_rudder_dir ~= 0 then

	elseif key_rudder_dir ~= 0 then
		des_rudder_ground = des_rudder_ground + key_rudder_dir
	elseif key_rudder_dir == 0 and des_rudder_ground ~= 0 and key_rudder_active == 1 then
		if des_rudder_ground < 0 then
			des_rudder_ground = des_rudder_ground + 0.01
		elseif des_rudder_ground > 0 then
			des_rudder_ground = des_rudder_ground - 0.01
		end
	end

	if Sensor_Data_Mod.nose_wow == 1 then
		if des_rudder_ground == mod_rudder_ground then

		elseif des_rudder_ground > mod_rudder_ground then
			mod_rudder_ground = mod_rudder_ground + 0.01
		elseif des_rudder_ground < mod_rudder_ground then
			mod_rudder_ground = mod_rudder_ground - 0.01
		end

		dispatch_action(nil, Keys.PlaneYawAxis, mod_rudder_ground)
	else
		dispatch_action(nil, Keys.PlaneYawAxis, (input_rudder * auth_rudder) + mod_rudder)
	end
end

function get_base_sensor_data()
	Sensor_Data_Raw = get_base_data()

	Sensor_Data_Mod = {
		rudder_pos = Sensor_Data_Raw.getRudderPosition(),
		mach       = Sensor_Data_Raw.getMachNumber(),
		nose_wow   = Sensor_Data_Raw.getWOW_NoseLandingGear(),
		AoA        = math.deg(Sensor_Data_Raw.getAngleOfAttack()), --is in rad?
		self_ias   = Sensor_Data_Raw.getIndicatedAirSpeed(), --m/s
		true_speed = Sensor_Data_Raw.getTrueAirSpeed(),
		--true_speed			= (3600 * (Sensor_Data_Raw.getTrueAirSpeed()))		/ 1000,
	}
end
