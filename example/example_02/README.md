Now we have a project that contains more than one file.
You can view these files in the subdirectory `files`.
It's actually the same as `example_01` but all commands and map events have been
moved to seperate modules which makes it much easier to work with.

In this directory there is a file called `example.4dv` which you can run
by typing

    $ 4dventure example.4dv

The output should be the same as if you're running

    $ 4dventure files/main.lua

This is because `example.4dv` is simply a zip archive containing all files in
out subdirectory `files`.

You can create your own archive by executing

    $ zip project.4dv file1 [file2, file3, ...]
 
Here file1 _must_ have one of the following filenames:

    * main
    * main.4dv
    * main.lua
    * main.4lua
    * init
    * init.4dv
    * init.lua
    * init.4lua

This is also the order of preference.
If you've got a file called `main.4dv`, a file called `main.lua` and a file
called `init` in your zip archive then `main.4dv` will be executed because it's
first in order of preference.

Please also note that your main file should _not_ contain a hashbang like
    
    #!/usr/bin/env 4dventure

So please remove it before adding to the archive.
