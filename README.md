# 4dventure v1.0 #

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

## INSTALLATION ##

### you need ###

 * gcc >= 4.7
 * glibc++
 * Lua 5.0 or 5.1 (otherwise you'll have to use the STANDALONE-Flag)
 * CMAKE >= 2.8

### How to install ###

    $ cd <this directory>
    $ mkdir bin && cd bin

If you have got Lua 5.0 or Lua 5.1 installed:

    $ cmake ../src
    $ make

Otherwise: 

    $ cmake ../src -DSTANDALONE=1
    $ make

To install globally:

    $ sudo make install
