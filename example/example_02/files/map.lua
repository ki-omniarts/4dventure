-- World map
local map = {}

--  S - is the start position. You'll have to put this tile into you map once(!)
--      or define the start position manually with adv_setPlayerPosition(x,y).
--      S is a predefined char just as $ (empty tile) is.
--  T - this tile will mark the target the player has to reach
--  _ - will mark a path
--  - - this is a bridge
--  ~ - water/river, we'll mark that as an obstacle later
--  ^ - mountains, they are an obstacle, too
--  
map.map = 
[[
^^^^^^^^^
^^~~~_^^^
^___-__S^
^T^^~~^^^
^^^^^^^^^
]];

function map.obstacle(string)
    if string == "^" then 
        -- if the player wants to enter a ^ tile
        -- we will tell him that there is a mountain
        print ("A mountain blocks your way.")
        -- and we tell 4dventure that the movement is unsuccessfull
        return true
    elseif string == "~" then
        -- the same goes for ~ tiles
        print ("A river blocks your way, you should use the bridge!")
        return true
    end
end

function map.onTile(string)
    if string == "_" or string == "S" then
        -- while the player walks on his path we want to print some "funny"
        -- random messages
        -- adv_random_ranged(ll,uu) gives you a random integer number 
        -- between ll and uu
        -- after that just check which one you've got
        local random = adv_random_ranged(0,2)
        if random == 0 then
            print ("Today is a beautiful day. "..
                "The sun is shining, birds are singing "..
                "and there is a smell of troll's excrements in the air...\n"..
                "\nLet's go home quickly!")
        elseif random == 1 then
            print ("Your garden looks very nice, "..
                "but why do you have a bridge with a troll in here?")
        elseif random == 2 then
            print ("Oh, you found a stone! "..
                "But you don't need it, there are enough of those around.")
        end
    elseif string == "-" then
        -- When the player enters the bridge he has to pay a fee to the troll
        print   ("There is a bridge in front of you. "..
                "A troll sits in front of it and gives you an angry glance.\n"..
                ">> Give me all your money or you shall not pass!\n"..
                "Do you want to give him your money to pass? (Y/N)")

        -- We check the input until the player entery "y" or "n"
        -- again we'll convert the input to lower case
        repeat
            print "Choose:"
            input = string.lower(adv_input()) or nil;
        until input == "y" or input == "n"

        -- Depending on the input we'll have another event
        if input == "Y" or input == "y" then
            print ("You pass the bridge quickly.")
            adv_goWest()
        else
            print ("You turn to the east and go away.")
            adv_goEast()
        end
    elseif string == "T" then
        -- When the player enters the target the game will exit
        print ("You just reached your house, congratulation!")
        adv_quit()
    end
end

return map;
