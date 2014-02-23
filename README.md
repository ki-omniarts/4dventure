# 4dventure v1.2.2 – Chuck the Plant #

## Are you ready for an 4dventure? ##

Do you remember the old days when text adventures where the best thing ever?
When ZORK started a big video game revolution?

4dventure brings back those days!

4dventure is an easy to use text adventure environment.
Just type a map using ASCII-charakters,
assign functions to simple commands
and be creative!

And if you need more than just that -- don't worry!
All scripting you want can be done in Lua, a simple
yet powerful programming language.

## Development ##

You can find the main repository at
http://ki-omniarts.de/hg/4dventure/
where the newest version will always be available for you.

If you like you can also check out our github mirror at
https://github.com/ki-omniarts/4dventure.

## Features ##

### Upcoming ###

 * Image Maps, Waypoint Maps, advanced Map API for dynamic Maps
 * zip File Support
 * Ingame Sounds
 * Some Lua libraries that will make your life easier
 * More Examples
 * Add an argument to `adv_input_INPUT` to parse the rest of the input string
 * An easy way to register Lua commands in the API
 * Give `adv_eachTurn()` a bool parameter that tells if there was a valid input
 * Support for configuration files and savestates
 * Multiplayer support

## INSTALLATION ##

### you need ###

 * gcc >= 4.7
 * glibc++
 * Lua (tested with 5.1 and 5.2)
 * CMAKE >= 2.8

### How to install ###

    $ cd <this directory>
    $ mkdir bin && cd bin
    $ cmake ../src [OPTIONS]

You might consider using some of the following options:

* `-DSTANDALONE=1` to build without Lua dependencies
* `-DLIBRARY=0` to turn off library building
* `-DBUILD_SHARED_LIBS=1` to build shared libs instead of static libs.

Notice that static libs will be installed in your local lib-Folder.

To build your files:

    $ make

To install globally:

    $ sudo make install

## Changelog ##

#### 1.2.2 ####

* Fixed SIGSEGV at empty user input
* Added `adv_emptyInput()` to catch an empty input in Lua

### 1.2.0 ###

* Customizeable "Command not found"-Message
* Customizeable quit Command
* Added Version Output and Version Getters for Lua

### 1.1.0 ###

* Cleaned up the code
* Added Library support, see __Installation__
