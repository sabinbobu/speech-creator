@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
call ..\Config\settings.bat

echo.
echo +++ 00_integration.bat: Start +++

if DEFINED CONFIGURATION (
  echo CONFIGURATION OPTION: %CONFIGURATION%
) else (
  echo CONFIGURATION OPTION: DEFAULT
)

rem Display the timestamp
call 02_timestamp.bat

rem DB maintenance
if %OPTION_USE_DB_MAINTENANCE%  GTR 0 call 10_db_maintenance.bat

rem Build main app
if %OPTION_USE_BUILD_APP%        == 1 call 20_build_app.bat

rem Evaluate if app was successfully built ***THIS BELONGS TO THE REPORT, IS EXECUTED SEPARATELY IN THE CI ENGINE
rem call 30_eval_app_build.bat

rem Evaluate compiler warnings
if %OPTION_USE_WARNING_PARSER%   == 1 call 40_run_warning.bat

rem Analyze the binary size with ALSize
if %OPTION_USE_SIZE_ANALYSIS%    == 1 call 42_analyze_size.bat

rem Calculate memory consumption
if %OPTION_USE_MAP_ANALYSIS%     == 1 (
  if %MAP_PARSER_TYPE% == Map_TricoreTasking (
    SET PARSER_STR=_tricoretasking
  ) else (
    SET PARSER_STR=
  )
  if %CONFIG_USE_MPU% == 1 (
    SET MPU_STR=_mpu
  ) else (
    SET MPU_STR=
  )
  call 45_analyze_map!PARSER_STR!!MPU_STR!.bat
)

rem Evaluate QAC + HIS metrics
if %OPTION_USE_QAC%              == 1 call 50_run_qac.bat

rem Perform AXIVION syntax checking
if %OPTION_USE_AXIVION%          == 1 call 51_run_axivion.bat

rem Build and evaluate all Unit tests
if %OPTION_USE_UNITTEST%         == 1 ( 
  call 60_run_all_ut_tests.bat
  if errorlevel 1 (
	exit /b 1
  ) else (
	echo ''' Build successful '''
  )
)

rem Build and evaluate all Integration tests
if %OPTION_USE_INTEGRATIONTEST%  == 1 call 65_run_all_it_tests.bat

rem Create report for the integrator
if %OPTION_USE_REPORT%           == 1 call 70_report_integration.bat

rem Also export data to doors
if %OPTION_USE_DOORS_EXPORT%     == 1 call 80_report_doors.bat

rem The overall report file is under:
rem \CI\TestResults\SingleFileReport.txt

echo.
echo +++ 00_integration.bat: Done +++
