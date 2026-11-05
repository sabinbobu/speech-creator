@echo off
SETLOCAL
call ..\Config\settings.bat

rem echo.
rem echo +++ Collecting source files +++

%PYTHON% scan_src.py > %CONFIG_PATH%\src.csv

rem echo.
rem echo +++ Collecting source files Done +++
