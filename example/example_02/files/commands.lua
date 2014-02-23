local commands = {}

-- We will save our commands in a table that holds tables as well:
-- command_table = { [key] , { [cmd] , [argc] , [return ] , [help] , [alias] } }
-- Here [key] is the command that will be entered by the user
-- [cmd] is a function that will be executed by command.execute(cmd,...)
-- [argc] is the number of arguments required, nil implies 0
-- [return] can provide a general return value, if nil function will be
-- returned
-- [help] is the text displayed by "help", it can be nil to indicate that there
-- is no help text
-- [alias] provides similar commands, which also is only relevant for "help"
-- and can be nil
local command_table = {}

-- {{{ quit
local function quit()
    print "Do you really want to quit this awesome game?! (y,[n])"
    input = string.lower(adv_input()) or nil;
    if input == "y" or input == "yes" then
        print "Bye :'("
        adv_quit()
    else 
        print "Hooray! You wanna stay!"
    end
    return true
end

command_table["quit"] = 
    { ["cmd"] = quit , ["help"] = "Lets you quit the game." , ["alias"] = "q" }
command_table["q"] = { ["cmd"] = quit }

-- }}} quit

-- {{{ movement
local function walk(dir)
    local dir = string.lower(dir)
    if     dir == "n" or dir == "north" then
        adv_goNorth()
    elseif dir == "e" or dir == "east"  then
        adv_goEast()
    elseif dir == "s" or dir == "south" then
        adv_goSouth()
    elseif dir == "w" or dir == "west"  then
        adv_goWest()
    else
        -- If the argument doesn't fit, we'll print an error message
        print ("Sorry, bro! This is no valid direction!")
    end

    return true
end

command_table["go"]     =
    { ["cmd"] = walk , ["argc"] = 1 , ["alias"] = "walk",
        ["help"] = "walk into a specific direction (n,s,e,w)" }
command_table["walk"]   = { ["cmd"] = walk , ["argc"] = 1 }
command_table["n"]      = { ["cmd"] = adv_goNorth , ["return"] = true }
command_table["north"]  = { ["cmd"] = adv_goNorth , ["return"] = true }
command_table["e"]      = { ["cmd"] = adv_goEast  , ["return"] = true }
command_table["east"]   = { ["cmd"] = adv_goEast  , ["return"] = true }
command_table["s"]      = { ["cmd"] = adv_goSouth , ["return"] = true }
command_table["south"]  = { ["cmd"] = adv_goSouth , ["return"] = true }
command_table["w"]      = { ["cmd"] = adv_goWest  , ["return"] = true }
command_table["west"]   = { ["cmd"] = adv_goWest  , ["return"] = true }
-- }}} movement

-- {{{ easter egg
local function ls()
    print ("This isn't your shell, you know?")
    return true
end

command_table["ls"]     = { ["cmd"] = ls }
command_table["ll"]     = { ["cmd"] = ls }
-- }}} easter egg

-- {{{ help
local function help()
    for k,v in pairs(command_table) do
        if v["help"] then
            if v["alias"] then
                print (k," - ",v["help"]," aliases: ",v["alias"])
            else
                print (k," - ",v["help"])
            end
        end
    end
    return true
end

command_table["help"]   = { ["cmd"] = help , ["help"] = "Show this text" }
-- }}} help

function commands.execute(cmd,...)
    if command_table[cmd]["argc"] == nil or
        ({...} and #{...} >= command_table[cmd]["argc"]) then
        if command_table[cmd]["return"] then
            command_table[cmd]["cmd"](...)
            return command_table[cmd]["return"]
        else
            return command_table[cmd]["cmd"](...)
        end
    else
        print "Not enough arguments for this command"
        return true
    end
end

return commands
