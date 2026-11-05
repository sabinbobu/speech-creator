@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ Run_all_it_tests.bat: Start +++

rem if exist ..\..\Build\Make\Make_005_UserSettings.gmk del ..\..\Build\Make\Make_005_UserSettings.gmk

rem Set the global test type to CTC or GCOV.
rem For the test automation and production purposes you must use CTC
rem This is configured in the settings
rem SET PAR_COVER=CTC
rem SET PAR_COVER=GCOV


rem TAILOR
rem call run_one_test.bat    It_SwcExample  Integration  %PAR_TEST%
rem call run_one_test.bat    It_All         Integration  %PAR_TEST%

echo.
echo +++ Run_all_it_tests.bat: Done +++
