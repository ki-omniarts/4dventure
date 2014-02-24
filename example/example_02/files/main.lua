-----------------------
-- 4dventure example --
-----------------------

local map = require("map")
local commands = require("commands")

-- Let's also print a Message when this file is loaded by 4dventure
print ("You're lost in your garden, you should try to find your house.")

-- Uncomment this line to have the Map printed in the beginning
--print(map)

-- We give the map to 4dventure
-- Note how we use the namespace `map` to adress a variable from another file
adv_setMap(map.map)

-- You can use a function called adv_eachTime() you want to have processed
-- each turn
function adv_eachTime()
    --x,y = adv_getPlayerPosition()

    --print(x)
    --print(y)
end

-- We just let commands handle this
function adv_input_(...)
    return commands.execute(...)
end

function adv_obstacle(string)
    return map.obstacle(string)
end

-- We also want to print out some text each time the player moves onto a tile
function adv_onTile(string)
    return map.onTile(string)
end
