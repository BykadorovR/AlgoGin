@echo off
set REL_PATH_FREEGLUT=freeglut\
set REL_PATH_GLEW=glew\

set ABS_PATH_DIR=%~dp0

REM set PATH_LIST_GLUT=%REL_PATH_FREEGLUT% %REL_PATH_FREEGLUT%lib\x64 %REL_PATH_FREEGLUT%lib\Win32 %REL_PATH_FREEGLUT%bin\x64 %REL_PATH_FREEGLUT%bin\Win32 - with x64
REM set PATH_LIST_GLEW=%REL_PATH_GLEW% %REL_PATH_GLEW%lib\Release\x64 %REL_PATH_GLEW%lib\Release\Win32 %REL_PATH_GLEW%bin\Release\x64 %REL_PATH_GLEW%bin\Release\Win32 - with x64

set PATH_LIST_GLUT=%REL_PATH_FREEGLUT% %REL_PATH_FREEGLUT%lib\Win32 %REL_PATH_FREEGLUT%bin\Win32
set PATH_LIST_GLEW=%REL_PATH_GLEW% %REL_PATH_GLEW%lib\Release\Win32 %REL_PATH_GLEW%bin\Release\Win32

for /f "tokens=2*" %%a in ('reg query "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path') do set "system_path=%%b"

:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"

REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params = %*:"=""
    echo UAC.ShellExecute "cmd.exe", "/c %~s0 %params%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"
:--------------------------------------

setlocal ENABLEDELAYEDEXPANSION
set new_path=
for %%c in (%PATH_LIST_GLUT%) do (
  SET system_path|FINDSTR /b "system_path="|FINDSTR /i %%c >nul
  IF ERRORLEVEL 1 (^
    set "new_path=!new_path!%ABS_PATH_DIR%%%c;"
    echo %%c
  )
)

for %%c in (%PATH_LIST_GLEW%) do (
  SET system_path|FINDSTR /b "system_path="|FINDSTR /i %%c >nul
  IF ERRORLEVEL 1 (^
    set "new_path=!new_path!%ABS_PATH_DIR%%%c;"
    echo %%c
  )  
)

reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path /t REG_SZ /d "%system_path%;!new_path!" /f
pause
