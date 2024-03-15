start_custom_command = 10000
local __count_custom = start_custom_command - 1
local function __custom_counter()
    __count_custom = __count_custom + 1
    return __count_custom
end


Keys          = {
    LeftRudderStart = 201,
    LeftRudderStop = 202,
    RightRudderStart = 203,
    RightRudderStop = 204,

    PowerOnOff = 315,

    PlaneYawAxis = 2003,
    PlaneThrustCommon = 2004,
    PlaneThrustLeft = 2005,
    PlaneThrustRight = 2006,

}

start_command = 3000
local __count = start_command - 1
local function __counter()
    __count = __count + 1
    return __count
end

device_commands =
{
    rudder_axis_left  = __counter(),
    rudder_axis_right = __counter(),
}

