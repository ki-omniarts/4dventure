map = 
[[
^^^^^^^^^
^^~~~_^^^
^___-__S^
^T^^~~^^^
^^^^^^^^^
]];

print ("You're lost in your garden, you should try to find your house.")

--print(map)

adv_setMap(map)

function adv_eachTime()
    --x,y = adv_getPlayerPosition()

    --print(x)
    --print(y)
end

function adv_input_help()
    print "n - Go northward"
    print "e - Go eastward"
    print "s - Go southward"
    print "w - Go westward"
end

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

function adv_input_ls()
    print ("This isn't your shell, you know?")
end

function adv_obstacle(string)
    if string == "^" then
        print ("A mountain blocks your way.")
        return true
    elseif string == "~" then
        print ("A river blocks your way, you should use the bridge!")
        return true
    end
end

function adv_onTile(string)
    if string == "-" then
        print   ("There is a bridge in front of you. "..
                "A troll sits in front of it and gives you an angry glance.\n"..
                ">> Give me all your money or you shall not pass!\n"..
                "Do you want to give him your money to pass? (Y/N)")
        repeat
            print "Choose:"
            input = adv_input();
        until input == "Y" or input == "y" or input == "N" or input == "n"

        if input == "Y" or input == "y" then
            print ("You pass the bridge quickly.")
            adv_input_w()
        else
            print ("You turn to the east and go away.")
            adv_input_e()
        end
    elseif string == "T" then
        print ("You just reached your house, congratulation!")
        adv_quit()
    elseif string == "_" or string == "S" then
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
    end
end
