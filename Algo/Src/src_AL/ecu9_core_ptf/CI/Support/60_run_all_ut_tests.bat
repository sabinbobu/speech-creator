@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ Run_all_ut_tests.bat: Start +++

rem if exist ..\..\Build\Make\Make_005_UserSettings.gmk del ..\..\Build\Make\Make_005_UserSettings.gmk

rem Set the global test type to CTC or GCOV.
rem For the test automation and production purposes you must use CTC
rem This is configured in the settings:
rem SET PAR_COVER=CTC
rem SET PAR_COVER=GCOV


rem TAILOR
call run_one_test.bat    Mt_ApplBenchmark  Unit         %PAR_TEST%


echo.
echo +++ Run_all_ut_tests.bat: Done +++

echo +++ Run JUnit Report Creation +++
call %PYTHON3% "parse_cunit_results.py" "..\..\Build\Bin" "..\..\cunit.xml"
