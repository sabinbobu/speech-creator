@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ 70_report_integration.bat: Start +++

if exist %SINGLE_FILE_REPORT% del %SINGLE_FILE_REPORT%

call do_report_integration.bat > %SINGLE_FILE_REPORT%

echo.
echo +++ 70_report_integration.bat: Done +++
