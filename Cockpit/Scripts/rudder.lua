local update_time_step = 0.016 --update will be called 60 times per second
make_default_activity(update_time_step)
dev = GetSelf()

local des_rudder_ground = 0
local mod_rudder_ground = 0

local key_rudder_active	= 0
local key_rudder_dir	= 0

local input_rudder      = 0

local auth_rudder	    = 1

local iCommandRudderAxis = 2003
dev:listen_command(iCommandRudderAxis)

local iCommandPlaneLeftRudderStart	= 201
local iCommandPlaneLeftRudderStop	= 202
local iCommandPlaneRightRudderStart	= 203
local iCommandPlaneRightRudderStop	= 204

dev:listen_command(iCommandPlaneLeftRudderStart)
dev:listen_command(iCommandPlaneLeftRudderStop)
dev:listen_command(iCommandPlaneRightRudderStart)
dev:listen_command(iCommandPlaneRightRudderStop)



function update()
    get_base_sensor_data()

    if Sensor_Data_Mod.nose_wow == 1 then 
        print_message_to_user("nose_wheel_down")
    end
	
	rudder()
end

function post_initialize()
	print_message_to_user("Init - rudder")
end

function SetCommand(command,value)
	
	if command == iCommandRudderAxis then
		key_rudder_active = 0
		if Sensor_Data_Mod.nose_wow == 1 then
			input_rudder 		= value
			des_rudder_ground   = round(value,2)
		else
			input_rudder = value
			des_rudder_ground =0
		end
	elseif command == iCommandPlaneLeftRudderStart then
		key_rudder_dir = - 0.01
		input_rudder = -1
			
	elseif command == iCommandPlaneRightRudderStart then
		key_rudder_dir =  0.01
		input_rudder = 1
			
	elseif command == iCommandPlaneRightRudderStop or command == iCommandPlaneLeftRudderStop then
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
		 
		dispatch_action(nil, 2003,mod_rudder_ground)
	else
		dispatch_action(nil, 2003,(input_rudder	* auth_rudder) 	+ mod_rudder)
	end
end
    

function get_base_sensor_data()

	Sensor_Data_Raw = get_base_data()
	
	Sensor_Data_Mod = 	{
							rudder_pos		= Sensor_Data_Raw.getRudderPosition(),
							mach			= Sensor_Data_Raw.getMachNumber(),
							nose_wow		= Sensor_Data_Raw.getWOW_NoseLandingGear(),
							AoA 			= math.deg(Sensor_Data_Raw.getAngleOfAttack()),		--is in rad?
							self_ias 			=  Sensor_Data_Raw.getIndicatedAirSpeed(),      --m/s
							true_speed			= Sensor_Data_Raw.getTrueAirSpeed()		,
							--true_speed			= (3600 * (Sensor_Data_Raw.getTrueAirSpeed()))		/ 1000,
						}	

end


function round(num, idp)
    local mult = 10^(idp or 0)
    return math.floor(num * mult + 0.5) / mult
end
