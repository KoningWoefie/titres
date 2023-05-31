# SH2D

## What you need
- Visual Studio Community 2019 or higher
- CMake
- doxygen
- git

---
## Windows 10/11
If you are in the directory of the repository you need to run these commands in powershell

```
mkdir build
cd build
cmake ..
```

If you have done that, the build directory should have a file named **SH2D.sln**. Double click this file and visual studio community will open up. You need to set a startup project, In this repository the project is named **titres**, you can change the name but be sure to change the **CMakeLists.txt** accordingly for each change of name or new files in the directory.

>If you do make new files, do **not** do so with visual studio community as it will not make the file in the correct directory.

<font size="6">Libraries</font>
- [GLFW](http://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [GLM](http://glm.g-truc.net/)