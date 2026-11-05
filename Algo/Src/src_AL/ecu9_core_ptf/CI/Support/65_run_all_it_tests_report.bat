@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Integration Test results ***
%DB_TOOL% %DB% < it_report_integration.sql
echo select ".width", "12", max(length(name)), "9" from v_it_results; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\it_report_integration.tmp
echo .headers on>> %UT_TMP%\it_report_integration.tmp
echo .mode column>> %UT_TMP%\it_report_integration.tmp
echo select * from v_it_results;>> %UT_TMP%\it_report_integration.tmp

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_it_results where lower(result)='passed';"`) DO SET COUNT_IT_PASSED=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_it_results where lower(result)='*failed*';"`) DO SET COUNT_IT_FAILED=%%F
echo Passed: %COUNT_IT_PASSED%   Failed: %COUNT_IT_FAILED%

%DB_TOOL% %DB% < %UT_TMP%\it_report_integration.tmp
