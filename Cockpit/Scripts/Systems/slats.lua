dofile(LockOn_Options.script_path .. "EFM_Data_Bus.lua")

local dev = GetSelf()
local efm_data_bus = get_efm_data_bus()
local update_time_step = 0.05 --20 time per second
make_default_activity(update_time_step)

local sensor_data = get_base_data()



local SLAT_STATE = 0


function update()
    slatL = efm_data_bus.fm_getSlatLeft()
    slatR = efm_data_bus.fm_getSlatRight()
    --print_message_to_user("L "..tostring(slatL).." R "..tostring(slatR))




    local t_ias = sensor_data.getIndicatedAirSpeed() * 1.9438444924574

    if (t_ias < 100) then
        SLAT_STATE = 1
    elseif (t_ias < 200) then
        SLAT_STATE = 1 - (t_ias / 100 - 1)
    end

    --set_aircraft_draw_argument_value(13,SLAT_STATE)
    --set_aircraft_draw_argument_value(14,SLAT_STATE)
end

need_to_be_closed = false -- close lua state after initialization
