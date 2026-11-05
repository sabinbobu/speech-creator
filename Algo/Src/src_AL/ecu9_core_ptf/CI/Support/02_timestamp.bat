@echo off
for /f %%a in ('powershell -Command "Get-Date -format yyyyMMdd-HHmm"') do set DATETIME=%%a

rem Extract the year, month, day from the date
set DT=%DATE:~9,4%%DATE:~6,2%%DATE:~3,2%
rem Zero-pad the date if it is before 10th
set DT=%DT: =0%

rem Extract the hour and minute from the time
set TM=%TIME:~0,2%%TIME:~3,2%
rem Zero-pad the hour if it is before 10am
set TM=%TM: =0%
rem echo Report creation timestamp: %DT%-%TM%

echo Report creation timestamp: %DATETIME%

echo %DATE% %TIME%
