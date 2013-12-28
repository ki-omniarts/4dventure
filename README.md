# 4dventure v1.1.0 #

## Are you ready for an 4dventure? ##

Do you remember the old days when text adventures where the best thing ever?
When ZORK started a big video game revolution?

4dventure brings back those days!

4dventure is an easy to use text adventure environment.
Just type a map using ASCII-charakters,
assign functions to simple commands
and be creative!

And if you need more then just that -- don't worry --
all scripting you like can be done in Lua!

## Future plans ##

We're planning to add options to compile 4dventure
as a static or shared library
allowing you to add more advanced features.

## Development ##

You can find the main repository at
http://ki-omniarts.de/hg/4dventure/
where there will always be the newest version online for you.

If you like you can also check out our github mirror at
https://github.com/ki-omniarts/4dventure.

## Features ##

### Upcoming ###

 * Ingame Sounds
 * Some Lua libraries that will make your life easier
 * More Examples
 * Add an argument to `adv_input_INPUT` to parse the rest of the input string

## INSTALLATION ##

### you need ###

 * gcc >= 4.7
 * glibc++
 * Lua 5.0 or 5.1 (otherwise you'll have to use the STANDALONE-Flag)
 * CMAKE >= 2.8

### How to install ###

    $ cd <this directory>
    $ mkdir bin && cd bin
    $ cmake ../src [OPTIONS]

You might consider using some of the following options:

* `-DSTANDALONE=1` to build without Lua dependencies
* `-DLIBRARY=0` to turn of library building
* `-DBUILD_SHARED_LIBS=1` to build shared libs instead of static libs.

Notice that static libs will be installed in your local lib-Folder.

To build your files:

    $ make

To install globally:

    $ sudo make install

## Changelog ##

### 1.1.0 ###

* Cleaned up the code
* Added Library support, see __Installation__
