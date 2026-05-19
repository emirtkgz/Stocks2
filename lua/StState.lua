-- Register global variables
period   = 30 * 24 * 3600
interval = "1d"

-- If an unknown global (etc. EURUSD) is given, format it as fetchSymbol("EURUSD", interval, period)
setmetatable(_G, {
    __index = function(t, key)
        -- Use these as, period and interval variables will be copied by value
        local p = rawget(t, "period")   or rawget(_G, "period")
        local i = rawget(t, "interval") or rawget(_G, "interval")

        local ok, val = pcall(fetchSymbol, key, i, p)
        if ok then
            return val
        else
            print("Lua: An error occured while formatting unknown global " .. key)
            print(val)
            return nil
        end
    end
})
