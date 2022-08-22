@ECHO OFF
REM Clean everything

ECHO "Cleaning everything..."

REM Engine
make -f ".\build\Makefile.src.mak" clean 
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% %% exit)

REM Testbed
make -f ".\build\Makefile.tests.mak" clean
IF %ERRORLEVEL% NEQ 0 (echo ERROR: %ERRORLEVEL% %% exit)

ECHO "All assemblies cleaned successfully."