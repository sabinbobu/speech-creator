@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Compiler warnings ***

%DB_TOOL% %DB% < w_report_integration.sql
echo select ".width", max(length(filename)), "-5 8 -9", max(length(error_text)) from v_compiler_results_al; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\w_report_integration.tmp
echo .headers on>> %UT_TMP%\w_report_integration.tmp
echo .mode column>> %UT_TMP%\w_report_integration.tmp
echo select * from v_compiler_results_al;>> %UT_TMP%\w_report_integration.tmp

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_compiler_results_al;"`) DO SET COUNT_WARNINGS=%%F
echo Count of AL warnings: %COUNT_WARNINGS%

rem echo List of compiler warnings:
%DB_TOOL% %DB% < %UT_TMP%\w_report_integration.tmp

rem ---------------------------------------------------------------------
echo.

echo select ".width", max(length(filename)), "-5 8 -9", max(length(error_text)) from v_compiler_results_n_al; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\w_report_integration.tmp
echo .headers on>> %UT_TMP%\w_report_integration.tmp
echo .mode column>> %UT_TMP%\w_report_integration.tmp
echo select * from v_compiler_results_n_al;>> %UT_TMP%\w_report_integration.tmp

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_compiler_results_n_al;"`) DO SET COUNT_WARNINGS=%%F
echo Count of third party warnings: %COUNT_WARNINGS%

rem echo List of compiler warnings:
%DB_TOOL% %DB% < %UT_TMP%\w_report_integration.tmp
