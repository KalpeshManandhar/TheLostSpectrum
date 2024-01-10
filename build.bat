@REM   .
@REM #  Compile your examples using:  raylib_makefile_example.bat core/core_basic_window
@REM #  .
@REM  Setup required Environment
@REM  -------------------------------------

@REM @echo off

set RAYLIB_BASE_DIR=E:\libraries\raylib\raylibMSVC\raylib-4.5.0_win64_msvc16
set RAYLIB_INCLUDE_DIR=%RAYLIB_BASE_DIR%\include
set RAYLIB_LIB_DIR=%RAYLIB_BASE_DIR%\lib
set SRC_DIR=.\src
set OUT_DIR=.\out


set SRC=%SRC_DIR%\**.cpp
set INCLUDES=-I%RAYLIB_INCLUDE_DIR%
set LIBS=-L%RAYLIB_LIB_DIR%
set LINKS=-lmsvcrt -lraylib -lOpenGL32 -lGdi32 -lWinMM -lkernel32 -lshell32 -lUser32
set EXE_NAME=TheLostSpectrum

@REM set RAYLIB_RES_FILE=C:\raylib\raylib\src\raylib.rc.data
@REM set FILENAME=%1
@REM set FILENAME_FULL_PATH=%~f1
@REM cd %~dp0

clang++ %INCLUDES% %LIBS% %SRC% -o %OUT_DIR%\%EXE_NAME%.exe  %LINKS% -Xlinker /NODEFAULTLIB:libcmt


copy %RAYLIB_LIB_DIR%\raylib.dll %OUT_DIR%\
