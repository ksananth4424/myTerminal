# This is myShell!!

This is an implementation of a few of the UNIX commands of linux terminal in C language.
The commands implemented are:
    1) ls
    2) cp
    3) mv
    4) ps
    5) grep

These commands are implemented without the use any system commands or using the computer to implement it for us.

The requirements to use this code are the following:
    -> A Linux Ubuntu machine.
    -> GCC available in the linux machine to comile the code.

        If GCC is not available in your linux Ubuntu machine then do the following to install GCC:
            open the terminal in your Linux Ubuntu machine and run the following command

                -> "sudo apt update"
                -> "sudo apt install build-essential"

            To check to if installed then run the command:

                -> "gcc --version"

    -> libreadline

        This will be automatically installed with other packages when we run the following commands:

            -> "sudo apt-get update"
            -> "sudo apt-get upgrade"

            or we can specifically install that with(replace the current version of libreadline whenever this is being read):

            -> "sudo apt-get install libreadline8 libreadline-dev"

To compile all the files at once and run the executable files:
    Go to the directory where all the files has been downloaded or cloned at and open the terminal at that directory then
    run this command:
        
        -> "make"

To execute the code run the following command:

    -> "./myShell"

For the available options of the commands implemented:

    type "(commands listed above) --help" to know imlpemented combinations.

NOTE: All the implementations may not resemble the actual UNIX commands/the linux terminal.


Author: K S Ananth.
 
Happy Coding!!
