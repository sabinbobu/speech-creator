@echo off
SETLOCAL
call ..\Config\settings.bat

rem echo.
rem echo +++ Analyzing the AlSize file +++

%PYTHON% analyze_size.py %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%_Size.txt %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%_Size_report.txt

rem echo.
rem echo +++ Analyzing the AlSize file Done +++
