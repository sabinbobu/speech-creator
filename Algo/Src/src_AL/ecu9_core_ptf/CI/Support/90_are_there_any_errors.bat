@echo off
SETLOCAL
call ..\Config\settings.bat

rem This file shows if there were any errors during the tests

set ERRORS_TOTAL=0


echo.
echo +++ Are there any errors? +++

echo.
echo Check errors in Unit Test compiler statistics
FOR /F %%I IN ('%DB_TOOL% %DB% "select count(*) from v_ut_results_compiler_statistics where result!='OK';"') DO SET UNIT_TEST_COMPILER_STAT_ERROR_COUNT=%%I
rem echo UNIT_TEST_COMPILER_STAT_ERROR_COUNT: %UNIT_TEST_COMPILER_STAT_ERROR_COUNT%
if %UNIT_TEST_COMPILER_STAT_ERROR_COUNT% NEQ 0 (
  set /A ERRORS_TOTAL=%ERRORS_TOTAL%+1
)


echo.
echo Check errors in Unit Test results
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_ut_results where lower(result)='*failed*';"`) DO SET COUNT_UT_FAILED=%%F
if %COUNT_UT_FAILED% NEQ 0 (
  set /A ERRORS_TOTAL=%ERRORS_TOTAL%+1
)


rem eval the collected error count
if %ERRORS_TOTAL% NEQ 0 (
  echo We have some problems.
  echo Exactly: %ERRORS_TOTAL%
) else (
  echo All went well.
)

echo.
echo +++ Are there any errors? Done +++

if %ERRORS_TOTAL% NEQ 0 (
  exit /b 1
) else (
  exit /b 0
)
