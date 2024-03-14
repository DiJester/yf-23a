dofile(LockOn_Options.script_path .. 'command_defs.lua')
dofile(LockOn_Options.script_path .. 'utils.lua')
dofile(LockOn_Options.script_path .. 'Systems/device_header.lua')

local dev              = GetSelf()

local update_time_step = 0.05 --update will be called 20 times per second
make_default_activity(update_time_step)


dev:listen_command(device_commands.rudder_axis_left)
dev:listen_command(device_commands.rudder_axis_right)

function post_initialize()
    print_message_to_user("rudder 2 initialized")
end

function SetCommand(command, value)
    -- rudder axis split (accessibility)
    if command == device_commands.rudder_axis_left then
        dispatch_action(nil, Keys.PlaneYawAxis, value * -0.5 - 0.5)
    elseif command == device_commands.rudder_axis_right then
        dispatch_action(nil, Keys.PlaneYawAxis, value * 0.5 + 0.5)
    end
end

function update()
end

need_to_be_closed = false
