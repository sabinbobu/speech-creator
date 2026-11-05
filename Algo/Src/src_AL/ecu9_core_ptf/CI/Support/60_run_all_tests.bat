@echo off
SETLOCAL
call settings.bat

echo.
echo +++ Run_all_tests.bat: Start +++

rem if exist ..\..\Build\Make\Make_005_UserSettings.gmk del ..\..\Build\Make\Make_005_UserSettings.gmk

rem Set the global test type to CTC or GCOV.
rem For the test automation and production purposes you must use CTC
rem This is configured in the settings
rem SET TESTTYPE=CTC
rem SET TESTTYPE=GCOV
SET TESTTYPE=%PAR_COVER%

rem TAILOR
call run_one_test.bat    Mt_ApplBenchmark  Unit         %PAR_TEST%  %TESTTYPE%


echo.
echo +++ Run_all_tests.bat: Done +++
