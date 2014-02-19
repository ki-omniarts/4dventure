-----------------------
-- 4dventure example --
-----------------------

-- First we'll define a map
-- each ASCII char represents a special type of tile
-- Here is what each char is supposed to mean in this example:
--  S - is the start position. You'll have to put this tile into you map once(!)
--      or define the start position manually with adv_setPlayerPosition(x,y).
--      S is a predefined char just as $ (empty tile) is.
--  T - this tile will mark the target the player has to reach
--  _ - will mark a path
--  - - this is a bridge
--  ~ - water/river, we'll mark that as an obstacle later
--  ^ - mountains, they are an obstacle, too
--  
map = 
[[
^^^^^^^^^
^^~~~_^^^
^___-__S^
^T^^~~^^^
^^^^^^^^^
]];

-- Let's also print a Message when this file is loaded by 4dventure
print ("You're lost in your garden, you should try to find your house.")

-- Uncomment this line to have the Map printed in the beginning
--print(map)

-- We give the map to 4dventure
adv_setMap(map)

-- You can use a function called adv_eachTime() you want to have processed
-- each turn
function adv_eachTime()
    --x,y = adv_getPlayerPosition()

    --print(x)
    --print(y)
end

-- This function will be executed when the user types "help"
-- It just prints some basic commands you can use
function adv_input_help()
    print "q - Quit game"
    print "n - Go northward"
    print "e - Go eastward"
    print "s - Go southward"
    print "w - Go westward"
end

-- It's always good to have a quit command
function adv_input_q()
    print "Do you really want to quit this awesome game?! (y,[n])"
    input = string.lower(adv_input()) or nil;
    if input == "y" or input == "yes" then
        print "Bye :'("
        adv_quit()
    else 
        print "Hooray! You wanna stay!"
    end
end


-- Those four functions will be executed it the player types n, s, e or w
-- They call predefined functions from 4dventure that will update the
-- players position
function adv_input_n()
    adv_goNorth()
end

function adv_input_s()
    adv_goSouth()
end

function adv_input_e()
    adv_goEast()
end

function adv_input_w()
    adv_goWest()
end

-- A little easter egg
function adv_input_ls()
    print ("This isn't your shell, you know?")
end

-- This function calls another adv_input_[string] function
-- That way you can simply define aliases
function adv_input_ll()
    adv_input_ls()
end

-- Here is another way to handle commands
-- This function will take whole user input word by word as seperate arguments
-- In fact, adv_input_[string](...) takes additional arguments as well
-- but this function becomes handy espacially if you want to have a command
-- that contains a space character, e.g. "pick up"
-- NOTE: if there is another function called adv_input_[string] that function
--       will be called!
-- In this case we just want to have some aliases for n,s,e,w
-- called "walk [dir]" and "go [dir]"
function adv_input_(string,...)
    -- Let's convert our first input string to lower case scince we don't care
    -- about if you type go, GO, Go or gO
    -- or leave it as nil if there are any errors (e.g. string could be nil)
    local command = string.lower(string) or nil 

    -- Now we'll check if command equals "go" or "walk"
    if command == "go" or command == "walk" then
        -- Again we convert the first argument that has to be the direction
        -- to lower case
        local s
    if arg then
    	if arg[1] then
	    s = string.lower(arg[1])
	end
    end

        -- Here we go through all our cases that could be directions
        if     s == "n" or s == "north" then
            adv_goNorth()
        elseif s == "e" or s == "east"  then
            adv_goEast()
        elseif s == "s" or s == "south" then
            adv_goSouth()
        elseif s == "w" or s == "west"  then
            adv_goWest()
        else
            -- If the argument doesn't fit, we'll print an error message
            print ("Sorry, bro! This is no valid direction!")
        end
        -- If command fits we have to tell 4dventure
        -- we do that by returning true
        return true
    end

    -- If command doesn't fit we have to tell 4dventure, too
    -- we do that by returning false
    return false
end

-- Remember our Map?
-- I mentioned that we'll mark ^ and ~ as obstacles
-- So let's do that by defining adv_obstacle(string)!
function adv_obstacle(string)
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

-- We also want to print out some text each time the player moves onto a tile
function adv_onTile(string)
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
            adv_input_w()
        else
            print ("You turn to the east and go away.")
            adv_input_e()
        end
    elseif string == "T" then
        -- When the player enters the target the game will exit
        print ("You just reached your house, congratulation!")
        adv_quit()
    end
end
