# IS F311: Computer Graphics
## Assignment 2
Part I: Create a scene of your choice with the help of simple primitives such as cubes, cuboids, torus, Utah’s teapot etc. Use openGL transformations to create props in the scene such as table, chair, benches, etc. Incorporate few objects made in 3D modelling software such as blender into your scene. 
Part II: Write functions to interact with your scene. Write functions to pan, zoom, pitch, yaw, and roll the camera

# Installation & Execution
1. A makefile has been created to simplify the process of compilation and building. Navigate to the directory with the source and run `make` to build the code. Please note that you will need the libraries GLFW, Glad and GLM for the compilation process to work. While the `glad.c` has been included in the source directory, you may have to download a different version if it doesn't work for you.
2. The code can be run using the command `./a.out`. The required blender exported resources are stored as `obj` and `mtl` files along with the source. You can interact with the object using your mouse to change orientation and the WASD keys to move the camera location.

# Documentation

Apart from this README, additional documentation has been provided in the form of HTML files and detailed comments in code that explain what each function and class does. HTML documentation has been generated using Doxygen, and the configuration file for the same can be seen in `.doxygen-config`. You can create the HTML files using the command `doxygen .doxygen-config` on any system that has doxygen installed. 

# General Discussion

Unlike assignment 1, for which we used the old OpenGL 2.x (GLUT), we decided to use the modern OpenGL (v3.3) primarily because most of the tutorials and learning resources discuss importing `.obj` files using Assimp and modern OpenGL. One challenge that we faced through the process was setting up libraries required to start coding. Installing the libraries required to setup the development environment was a pretty time taking process. We had to install most of the required libraries from source, and for `Glad` we had to use a [web service](http://glad.dav1d.de/) to get the requisite library version up and running. After being used to `apt install`-ing libraries and everything just working, spending multiple hours to setup the development environment was quite a change. Adding to this problem was the fact that some of our team members used different versions of Linux/Ubuntu, while the other used Windows, making it harder for us to effectively help each other out. Even after this, the Hello World program of drawing a triangle, required setting up and compiling two shaders, linking them with a program, creating Vertex Buffer and Array objects, and then setting up a loop in which we drew the final triangle. Quite a bit of code to draw one figure, and a steep learning curve. 

Learning Blender was relatively the most straightforward part of this assignment. After this, figuring out a way to import `obj` files to OpenGL was again challenging - at one point we were tempted to go back to OpenGL 2.x and just write a function ourselves to read `obj` files, which is what some tutorials we saw online did. After lots of trial and error, Assimp finally worked though.

# Resources Used

1. [Learn OpenGL](learnopengl.com)
2. [OpenGL Beginners Tutorial](http://www.opengl-tutorial.org/beginners-tutorials/)