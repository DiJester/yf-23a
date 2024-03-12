start_custom_command = 10000
local __count_custom = start_custom_command - 1
local function __custom_counter()
    __count_custom = __count_custom + 1
    return __count_custom
end


Keys = {
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
