# Solar Sim
## Description
This project simulates a solar system consisting of a sun, earth, and moon represented by cubes. It is built in C++ using the OpenGL API along with the following libraries:
1. GLFW3
2. GLAD
3. GLM

Below is a video displaying how the project runs:

[![YouTube](http://i.ytimg.com/vi/Rwsw86FiF3Q/hqdefault.jpg)](https://www.youtube.com/watch?v=Rwsw86FiF3Q)

## Setup
To setup the project, you need to setup the GLFW3, GLAD, and GLM libraries. Follow the steps in the following link to setup GLFW3, GLAD, and other system specific dependencies, https://learnopengl.com/Getting-started/Creating-a-window. Furthermore, the `glad.c` file must be placed in the `src/` folder. You can use the official glm github page to install and setup the library https://github.com/g-truc/glm. 

After setting up all the libraries, open `Makefile` and add your include and lib paths.
```Make
INCDIR = # Include dir that contains glfw3, glad, and GLM header files
LIBDIR = # Lib dir that contains glfw3, glad, and GLM library files
```

## How to run
To run this project, execute the `run.sh` shell script. This will build and start the application. You can also build the application yourself by running in the root directory of the project.
``` sh
make
```
After building the project, the executable will be found in the `src/` folder. For the executable to propery run the application, you must run the executable from within the `src/` folder.
```sh
cd src/
./SolarSim
```
