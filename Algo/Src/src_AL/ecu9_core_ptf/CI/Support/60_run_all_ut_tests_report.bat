@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Unit Test compiler statistics ***
%DB_TOOL% %DB% < ut_report_compilerstatistics.sql
echo select ".width", max(max(length(project)),7), "6" from v_ut_results_compiler_statistics; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\ut_report_compilerstatistics.tmp
echo .headers on>> %UT_TMP%\ut_report_compilerstatistics.tmp
echo .mode column>> %UT_TMP%\ut_report_compilerstatistics.tmp
echo select project, result from v_ut_results_compiler_statistics;>> %UT_TMP%\ut_report_compilerstatistics.tmp

%DB_TOOL% %DB% < %UT_TMP%\ut_report_compilerstatistics.tmp


echo.
echo.
echo *** Unit Test results ***
%DB_TOOL% %DB% < ut_report_integration.sql
echo select ".width", "5", max(length(name)), "9" from v_ut_results; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\ut_report_integration.tmp
echo .headers on>> %UT_TMP%\ut_report_integration.tmp
echo .mode column>> %UT_TMP%\ut_report_integration.tmp
echo select * from v_ut_results;>> %UT_TMP%\ut_report_integration.tmp

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_ut_results where lower(result)='passed';"`) DO SET COUNT_UT_PASSED=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) from v_ut_results where lower(result)='*failed*';"`) DO SET COUNT_UT_FAILED=%%F
echo Passed: %COUNT_UT_PASSED%   Failed: %COUNT_UT_FAILED%

%DB_TOOL% %DB% < %UT_TMP%\ut_report_integration.tmp


echo.
echo.
echo *** Module coverage statistics ***
%DB_TOOL% %DB% < co_report_integration.sql

echo select ".width", max(length(Project)), "-11", "-11", "-11", "-11", "-11", "-11" from v_ut_coverage_module; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\ut_coverage_module.tmp
echo .headers on>> %UT_TMP%\ut_coverage_module.tmp
echo .mode column>> %UT_TMP%\ut_coverage_module.tmp
echo select * from v_ut_coverage_module;>> %UT_TMP%\ut_coverage_module.tmp
%DB_TOOL% %DB% < %UT_TMP%\ut_coverage_module.tmp


echo.
echo.
echo *** Function coverage statistics ***
rem %DB_TOOL% %DB% < co_report_integration.sql
echo select ".width", "-10", "-10", max(length(function_name)), max(length(project)) from v_ut_coverage; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\co_report_integration.tmp
echo .headers on>> %UT_TMP%\co_report_integration.tmp
echo .mode column>> %UT_TMP%\co_report_integration.tmp
echo select * from v_ut_coverage;>> %UT_TMP%\co_report_integration.tmp

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest;"`) DO SET COUNT_TOTAL=%%F
SET "OUTPUT=%SPACES%%COUNT_TOTAL%"
echo Count of functions total              : %OUTPUT:~-5%


FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest where C0_percent=100;"`) DO SET COUNT_FULLCOV_C0=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest where C1_percent=100;"`) DO SET COUNT_FULLCOV_C1=%%F
SET "OUTPUT0=%SPACES%%COUNT_FULLCOV_C0%"
SET "OUTPUT1=%SPACES%%COUNT_FULLCOV_C1%"
echo Count of functions with  100%% coverage: %OUTPUT0:~-5% %OUTPUT1:~-5%

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest where 0<C0_percent and C0_percent<100;"`) DO SET COUNT_1_99_COV_C0=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest where 0<C1_percent and C1_percent<100;"`) DO SET COUNT_1_99_COV_C1=%%F
SET "OUTPUT0=%SPACES%%COUNT_1_99_COV_C0%"
SET "OUTPUT1=%SPACES%%COUNT_1_99_COV_C1%"
echo Count of functions with 99-1%% coverage: %OUTPUT0:~-5% %OUTPUT1:~-5%

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest where C0_percent=0;"`) DO SET COUNT_ZEROCOV_C0=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select count(*) as c from v_ut_coverage_latest where C1_percent=0;"`) DO SET COUNT_ZEROCOV_C1=%%F
SET "OUTPUT0=%SPACES%%COUNT_ZEROCOV_C0%"
SET "OUTPUT1=%SPACES%%COUNT_ZEROCOV_C1%"
echo Count of functions with    0%% coverage: %OUTPUT0:~-5% %OUTPUT1:~-5%

%DB_TOOL% %DB% < %UT_TMP%\co_report_integration.tmp
