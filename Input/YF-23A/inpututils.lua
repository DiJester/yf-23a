function Ignore_names(commands, names)
    if commands == nil or names == nil then
        return
    end

    local namesHashTable = {}

    for i, name in ipairs(names) do
        namesHashTable[name] = true
    end

    for i = #commands, 1, -1 do
        local command = commands[i]

        if command.name and namesHashTable[command.name] then
            table.remove(commands, i)
        end
    end
end
