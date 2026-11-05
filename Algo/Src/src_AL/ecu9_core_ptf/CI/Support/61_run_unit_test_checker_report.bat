@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
rem Test file inconsistencies
REM TODO: make this a list of paths
%PYTHON% unit_test_checker.py  ../../  %UT_PATH%
