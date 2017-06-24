@echo off

set REL_PATH_FREEGLUT=freeglut\
set REL_PATH_GLEW=glew\
set ABS_PATH_FREEGLUT=
set ABS_PATH_GLEW=

rem // Save current directory and change to target directory
pushd %REL_PATH_FREEGLUT%

rem // Save value of CD variable (current directory)
set ABS_PATH_FREEGLUT=%CD%

rem // Restore original directory
popd


rem // Save current directory and change to target directory
pushd %REL_PATH_GLEW%

rem // Save value of CD variable (current directory)
set ABS_PATH_GLEW=%CD%

rem // Restore original directory
popd


echo %ABS_PATH_FREEGLUT%
echo %ABS_PATH_FREEGLUT%\lib\x64
echo %ABS_PATH_FREEGLUT%\lib\Win32
echo %ABS_PATH_FREEGLUT%\bin\x64
echo %ABS_PATH_FREEGLUT%\bin\Win32;
echo %ABS_PATH_GLEW%
echo %ABS_PATH_GLEW%\lib\Release\x64
echo %ABS_PATH_GLEW%\lib\Release\Win32
echo %ABS_PATH_GLEW%\bin\Release\x64
echo %ABS_PATH_GLEW%\bin\Release\Win32
