dofile(LockOn_Options.script_path .. 'command_defs.lua')
dofile(LockOn_Options.script_path .. 'utils.lua')
dofile(LockOn_Options.script_path .. 'Systems/device_header.lua')
local dev = GetSelf()
local update_time_step = 0.02
make_default_activity(update_time_step) -- enables call to update

dev:listen_command(Keys.PowerOnOff)
dev:listen_event(CptEvntNames.gndPwrOn)
dev:listen_event(CptEvntNames.gndPwrOff)
dev:listen_event(CptEvntNames.canopyOpen)
dev:listen_event(CptEvntNames.canopyClose)

function post_initialize()
    print_message_to_user("DEMO Device Intialized")
    local initType = LockOn_Options.init_conditions.birth_place
    if initType == 'GROUND_COLD' then
        print_message_to_user("Ground Cold Start", 3)
    elseif initType == 'GROUND_HOT' then
        print_message_to_user("Ground Hot Start", 3)
    elseif initType == 'AIR_HOT' then
        print_message_to_user("Air Hot Start", 3)
    end
end

function SetCommand(command, value)
    if command == Keys.PowerOnOff then
        print_message_to_user("Power ON/OFF Command Captured")
    end
end

function update()
    print_message_to_user('IAS===' .. BASE_SENSOR.IAS.get() * (3600 / 1000))
    print_message_to_user('TAS===' .. BASE_SENSOR.TAS.get() * (3600 / 1000))
    print_message_to_user('Mach===' .. BASE_SENSOR.MACH.get())
    print_message_to_user("ALT==" .. BASE_SENSOR.BAROALT.get())
    print_message_to_user("RALT==" .. BASE_SENSOR.RADALT.get())
    print_message_to_user("G==" .. BASE_SENSOR.VERTICAL_ACCEL.get())
    print_message_to_user("MAG Heading==" .. BASE_SENSOR.MAG_HEADING.get())
    print_message_to_user("Heading==" .. BASE_SENSOR.HEADING.get())

    print_message_to_user('Left Engine RPM==' .. BASE_SENSOR.LEFT_ENGINE_RPM.get())
    print_message_to_user('Right Engine RPM==' .. BASE_SENSOR.RIGHT_ENGINE_RPM.get())
    print_message_to_user('Left Before Turbine Temp==' .. BASE_SENSOR.LEFT_ENGINE_TEMP_BEFORE_TURBINE.get())
    print_message_to_user('Right Before Turbine Temp==' .. BASE_SENSOR.RIGHT_ENGINE_TEMP_BEFORE_TURBINE.get())
    print_message_to_user('Left Engine Fuel Flow==' .. BASE_SENSOR.LEFT_ENGINE_FUEL_CONSUPMTION.get())
    print_message_to_user('Right Engine Fuel Flow==' .. BASE_SENSOR.RIGHT_ENGINE_FUEL_CONSUPMTION.get())
    print_message_to_user('Left Throttle Position==' .. BASE_SENSOR.LEFT_THROTTLE_POS.get())
    print_message_to_user('Right Throttle Position==' .. BASE_SENSOR.RIGHT_THROTTLE_POS.get())
    print_message_to_user('Left Throttle Raw Control==' .. BASE_SENSOR.LEFT_THROTTLE_RAW_CONTROL.get())
    print_message_to_user('Right Throttle Raw Control==' .. BASE_SENSOR.RIGHT_THROTTLE_RAW_CONTROL.get())
end

function CockpitEvent(event, value)
    if event == CptEvntNames.gndPwrOn then
        print_message_to_user("Ground power is on", 3)
    elseif event == CptEvntNames.gndPwrOff then
        print_message_to_user("Ground power is off", 3)
    elseif event == CptEvntNames.canopyOpen then
        print_message_to_user("Canopy is open", 3)
    elseif event == CptEvntNames.canopyClose then
        print_message_to_user("Canopy is closed", 3)
    end
end

need_to_be_closed = false
