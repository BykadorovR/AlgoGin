@echo off
set REL_PATH_FREEGLUT=freeglut\
set REL_PATH_GLEW=glew\

set ABS_PATH_DIR=%~dp0

set PATH_LIST_GLUT=%REL_PATH_FREEGLUT% %REL_PATH_FREEGLUT%lib\x64 %REL_PATH_FREEGLUT%lib\Win32 %REL_PATH_FREEGLUT%bin\x64 %REL_PATH_FREEGLUT%bin\Win32
set PATH_LIST_GLEW=%REL_PATH_GLEW% %REL_PATH_GLEW%lib\Release\x64 %REL_PATH_GLEW%lib\Release\Win32 %REL_PATH_GLEW%bin\Release\x64 %REL_PATH_GLEW%bin\Release\Win32

echo %PATH%
for %%a in (%PATH_LIST_GLUT%) do (
   echo %%a
   echo "%PATH%" | find /C /I "%%a"
)
for %%a in (%PATH_LIST_GLEW%) do ( 
   echo %%a
)

REM SET path_extended=
REM reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path /t REG_SZ /d "%path%;%path_extended%"

echo %PATH% | find /C /I "%ABS_PATH_FREEGLUT%"

pause
