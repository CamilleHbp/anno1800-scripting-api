# Anno1800-Scripting-API

?> If you are viewing this on Github, you should know that this documentation is available in a nicer format as a website [here]()

## What is it?

A tool to make scripts for Anno 1800.

The idea of the project is to implement a scripting interface with [Anno 1800](https://www.ubisoft.com/en-us/game/anno-1800/). The game itself allows users to control most things through the UI, including shipping goods via trade routes. The goal of this project is to expose as much of those functionnalities as possible through a C# scripting API.

There is a main program communicating with the game, and other programs using this API to add functionnalities.

What can I do now?

### Disclaimer

!> **Non-affiliated project !** This project is in no way affiliated with Ubisoft Blue Byte or Ubisoft

!> **Using this project might count as cheating, so be careful** !

This is a pet/passion/hobby project! No guarantees and no promises.

I never coded anything of this kind before, so expect some limitations :P Finally, if you look through the code you will notice that many places are quite messy. Since I've never done this before and the game changes I cannot tell if certain techniques work or not. Much of the code could use a caring hand...

I would however love any feedback on any aspect of the code!

## I want to use it

First you need to install the program. You have 2 possibilities, install the stable version or build the program yourself to get the latest -and probably unstable- changes.

### I want to use the stable version

Just head to the [releases]() and download the latest version. Install the program

### I want to use the edge version

You need to build the project on your windows computer. You can follow the [building instructions]().

## I want to contribute

Please see the [contributing page](CONTRIBUTING.md)

### Getting started

**How to install and use**

I will probably change a lot when I'm happier with the code. But at current, following should work.

* Clone the repo to a local folder
* Build the Anno1800ScriptingAPI.sln solution file (in debug mode)
* Run Anno 1800
* Configure the debugging settings by specifying $(TargetDir) as the working directory, as can be seen in the following image doc/surveillancevan_debug_config.png
    Launch the solution (still in debug mode)
* Run code using the monocle project (**with administrator rights**)
