@echo off
SETLOCAL
call settings.bat

echo.
echo +++ 70_do_report_integration.bat: Start +++

if exist %SINGLE_FILE_REPORT% del %SINGLE_FILE_REPORT%

call report_integration.bat > %SINGLE_FILE_REPORT%

echo.
echo +++ 70_do_report_integration.bat: Done +++
