echo IoHwAb conversion helper
@echo off

set PATH_TOOLS_GENERIC_BASE=.\..\..\..\ToolsGeneric
set PYTHONCMD=%PATH_TOOLS_GENERIC_BASE%\Utilities\CommonDomain\python\python383\python.exe

set PYTHONPARAMS=IoHwAb.py

%PYTHONCMD% %PYTHONPARAMS%

pause