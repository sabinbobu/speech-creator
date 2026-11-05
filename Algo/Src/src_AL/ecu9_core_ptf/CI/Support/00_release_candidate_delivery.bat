@echo off

echo.
echo +++ 00_release_candidate_delivery.bat: Start +++

rem Display the timestamp
call 02_timestamp.bat

rem DB maintenance
call 10_db_maintenance.bat

rem Build main app
call 20_build_app_delivery.bat

rem Evaluate if app was successfully built ***THIS BELONGS TO THE REPORT, IS EXECUTED SEPARATELY IN THE CI ENGINE
rem call 30_eval_app_build.bat

rem Evaluate compiler warnings
call 40_run_warning.bat

rem Analyze the binary size with ALSize
call 42_analyze_size.bat

rem Calculate memory consumption
call 45_analyze_map.bat

rem Evaluate QAC + HIS metrics
call 50_run_qac.bat

rem Build and evaluate all Unit and Integration tests
call 60_run_all_tests.bat

rem Create report for the integrator
call 70_do_report_integration.bat

rem Also export data to doors
call 80_report_doors.bat

rem The overall report file is under:
rem \CI\TestResults\SingleFileReport.txt

echo.
echo +++ 00_release_candidate_delivery.bat: Done +++
