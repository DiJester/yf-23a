dofile(LockOn_Options.script_path .. 'command_defs.lua')
dofile(LockOn_Options.script_path .. 'utils.lua')
dofile(LockOn_Options.script_path .. 'Systems/device_header.lua')

local dev              = GetSelf()

local update_time_step = 0.016 --update will be called 60 times per second
make_default_activity(update_time_step)

local key_rudder_dir     = 0

local key_input_rudder   = 0
local axis_input_rudder  = 0
local input_rudder       = 0

local auth_rudder        = 1
local rudder_limit_gs    = 5.0
local rudder_maneu_speed = 0.032
local rudder_neu_speed   = 0.06


dev:listen_command(device_commands.rudder_axis_mod)
dev:listen_command(device_commands.left_rudder_start)
dev:listen_command(device_commands.left_rudder_stop)
dev:listen_command(device_commands.right_rudder_start)
dev:listen_command(device_commands.right_rudder_stop)


function update()
	--get_base_sensor_data()

	rudder()
end

function post_initialize()
	print_message_to_user("Init - rudder")
end

function SetCommand(command, value)
	print_message_to_user("detected command" .. command .. "value" .. value)
	if command == device_commands.rudder_axis_mod then
		print_message_to_user("rudder_axis_mod" .. value)
		axis_input_rudder = value
	elseif command == device_commands.left_rudder_start then
		print_message_to_user("left_rudder_start")
		key_rudder_dir = -1
	elseif command == device_commands.right_rudder_start then
		print_message_to_user("right_rudder_start")

		key_rudder_dir = 1
	elseif command == device_commands.left_rudder_stop or command == device_commands.right_rudder_stop then
		print_message_to_user("rudder_stop")
		key_rudder_dir = 0
	end
end

function rudder()
	local keyRudderMag = math.abs(key_input_rudder)
	local keyRudderSign = 1
	if key_input_rudder < 0 or (key_input_rudder == 0 and key_rudder_dir == -1) then
		keyRudderSign = -1
	end

	if isNeutralizing(key_rudder_dir, key_input_rudder) then
		keyRudderMag = clamp(keyRudderMag - rudder_neu_speed, 0, 1)
	else
		keyRudderMag = clamp(keyRudderMag + rudder_maneu_speed, -1, 1)
	end

	key_input_rudder = keyRudderMag * keyRudderSign
	input_rudder = clamp(axis_input_rudder + key_input_rudder, -1, 1)

	if input_rudder ~= 0 then
		local gs = GetGroundSpeed()
		if gs <= rudder_limit_gs then
			auth_rudder = gs * gs / (rudder_limit_gs * rudder_limit_gs)
		else
			auth_rudder = 1
		end
		dispatch_action(nil, Keys.PlaneYawAxis, input_rudder * auth_rudder)
	end
end

function isNeutralizing(keyRudderDir, keyRudderInput)
	if keyRudderInput ~= 0 then
		local result = keyRudderDir * keyRudderInput
		if result <= 0 then
			return true
		else
			return false
		end
	elseif keyRudderDir ~= 0 then
		return false
	else
		return true
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
