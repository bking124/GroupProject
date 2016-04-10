#Configuration

**PC - CodeBlocks**

1. Download and install - freeglut
	* http://freeglut.sourceforge.net/
	* C:\MinGW\freeglut
2. Linker
	* Settings->Compiler and debugger ... -> Linker settings
	* -lOpenGL32 -lglu32 -lfreeglut
	* Project Build Options
	* Compiler: path to freeglut include
	* Linker: path to freeglut lib
	* Settings->Compiler and debugger ... -> Search directories
	*C:\MinGW\freeglut\include
3. Include the following file
	* <GL/freeglut.h>
4. freeglut tutorial
	* http://lazyfoo.net/tutorials/OpenGL/01_hello_opengl/windows/index.php

**Mac - OSX**

1. framework GLUT -framework openGL -framework Cocoa
