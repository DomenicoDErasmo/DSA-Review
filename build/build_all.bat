@ECHO OFF
REM Build Everything
ECHO "Building everything..."

REM Engine
make -f "./build/Makefile.src.mak" build
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

make -f "./build/Makefile.tests.mak" build
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully." 