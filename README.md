Piet
====

[Piet](http://en.wikipedia.org/wiki/Piet_%28programming_language%29) is a graphical programming language designed by [David Morgan-Mar](http://en.wikipedia.org/wiki/David_Morgan-Mar). Read more about Piet at http://www.dangermouse.net/esoteric/piet.html.

This project provides Piet interpreter lib which is additionally used inside a console and gui aplications. 

Compilation
===========

The project uses [CMake](http://www.cmake.org/) for deployment process. You need to have installed version 2.8.2 or higher. Once cmake is installed, you may compile with following commands:

    mkdir build
    cd build
    cmake ..
    make

and it will create all binary files (libs, console and gui application).

Doxygen
=======

If you have doxygen documentation tool installed, cmake will additionally generate HTML documentation.

Qt Creator
==========

You may use the Qt Creator tool within the gui project (sources are located in src/gui). Open the project with the `gui.pro` file. But before you can compile the gui application in the Qt Creator, libpietcore.a library has to be compiled (which is done by cmake). Basically, compile entire project with cmake and after this you can use Qt Creator with no limits.

Run
===

Execute the `piet` binary file in command line with one parameter, specifying the program to execute:

    $ piet path_to_img_programs/2toN.png

Travis continuous integration
=============================

Piet project code is integrated with travis, where it is compiled using Qt4 and cmake:

[![Build Status](https://travis-ci.org/ducin/piet.png?branch=master)](https://travis-ci.org/tkoomzaaskz/piet)
