start_custom_command = 10000
local __count_custom = start_custom_command - 1
local function __custom_counter()
    __count_custom = __count_custom + 1
    return __count_custom
end


Keys = {
    -- iComandPlaneLeftRudderStart    = 201,
    -- iComandPlaneLeftRudderStop     = 202,
    -- iComandPlaneRightRudderStart   = 203,
    -- iComandPlaneRightRudderStop    = 204,

    PowerOnOff        = 315,

    PlaneYawAxis      = 2003,
    PlaneThrustCommon = 2004,
    PlaneThrustLeft   = 2005,
    PlaneThrustRight  = 2006,

    LeftRudderStart   = __custom_counter(),
    LeftRudderStop    = __custom_counter(),
    RightRudderStart  = __custom_counter(),
    RightRudderStop   = __custom_counter(),
}


start_command = 3000
local __count = start_command - 1
local function __counter()
    __count = __count + 1
    return __count
end

device_commands =
{
    Button_Test     = __counter(),
    rudder_axis_mod = __counter(),
}
