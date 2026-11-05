@echo off

tasklist /FI "IMAGENAME eq Exam.exe" 2>NUL | find /I /N "Exam.exe">NUL
if "%ERRORLEVEL%"=="0" ( 
echo EXAM is running killing exam now ...
taskkill /f /im EXAM.exe
) else (
echo opening exam for db connection
START D:\EXAM44\EXAM\EXAM.exe -data "D:\EXAM44\userData\workspace" -configuration "D:\EXAM44\userData\configuration"
rem TIMEOUT 60
powershell Start-Sleep -s 60
taskkill /f /im EXAM.exe
)

rem set TESTRUN=RestbusRegressionTest
set EXAMEXE=D:\EXAM44\EXAM\EXAM.exe
set EXAMWRKSPC=D:\EXAM44\userData\workspace
set EXAMCFGDIR=D:\EXAM44\userData\configuration
set EXAMREPORT=D:\EXAM44\userData\reports\
set EXAMEXECFILE=%cd%\LDM_SUITE.xml
rem for /f %%a in ('powershell -Command "Get-Date -format yyyy_MM_dd__HH_mm_ss"') do set DATETIME=%%a

echo call %EXAMEXE% -configuration %EXAMCFGDIR% -e %EXAMEXECFILE% -m start_exit -l DEBUG -data %EXAMWRKSPC%
%EXAMEXE% -configuration %EXAMCFGDIR% -e %EXAMEXECFILE% -m start_exit -l DEBUG -data %EXAMWRKSPC%


rem pushd %EXAMREPORT%
REM Get list of all directories sorted by date and list it reverse (top newest)
rem for /F "delims=" %%i in ('dir /AD /O-D /B') do (
rem    7z a -mx9 %DATETIME%%TESTRUN%.7z -x!%DATETIME%%TESTRUN%.*
rem )
rem popd

