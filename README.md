# MechaJamEngine
A basic 2D engine written in c++ using opengl as well as various other dependencies.
Dependencies are included in the project so building should work.
The only thing not included are the resource files, probably will just use share and zip.

## Code Design / Engine Layout
I want the design and the code to be simple and performant. This is also the first engine that I've written so there's probably 
gonna be some things that aren't optimal. The main design I'm using right now is to just group functionality together in files 
and directories that make sense. Why are some things classes when they could be functions or could lumped together in the same 
file? Keeping things clear and organized sensibly is what I'm shooting for.