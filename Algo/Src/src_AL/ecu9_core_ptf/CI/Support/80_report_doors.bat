@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ Export data to Doors Start +++

echo.
echo Exporting Unit Test results to CSV
%DB_TOOL% %DB% < v_ut_report_doors.sql
echo .headers on> %UT_TMP%\export_ut_results.tmp
echo .mode csv>> %UT_TMP%\export_ut_results.tmp
echo .output %REPORT_PATH_SQL%\\export_ut_results.csv>> %UT_TMP%\export_ut_results.tmp
echo select * from v_ut_report_doors>> %UT_TMP%\export_ut_results.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_ut_results.tmp


echo.
echo Exporting Integration Test results to CSV
%DB_TOOL% %DB% < v_it_report_doors.sql
echo .headers on> %UT_TMP%\export_it_results.tmp
echo .mode csv>> %UT_TMP%\export_it_results.tmp
echo .output %REPORT_PATH_SQL%\\export_it_results.csv>> %UT_TMP%\export_it_results.tmp
echo select * from v_it_report_doors>> %UT_TMP%\export_it_results.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_it_results.tmp


echo.
echo Exporting Timestamp to CSV
echo .headers on> %UT_TMP%\export_timestamp.tmp
echo .mode csv>> %UT_TMP%\export_timestamp.tmp
echo .output %REPORT_PATH_SQL%\\export_timestamp.csv>> %UT_TMP%\export_timestamp.tmp
echo select * from ( (select max(date) as date from ut_results), (select max(time) as time from ut_results where date = (select max(date) from ut_results)) )>> %UT_TMP%\export_timestamp.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_timestamp.tmp


echo.
echo Exporting Module memory footprint to CSV
echo .headers on> %UT_TMP%\export_memory_footprint.tmp
echo .mode csv>> %UT_TMP%\export_memory_footprint.tmp
echo .output %REPORT_PATH_SQL%\\export_memory_footprint.csv>> %UT_TMP%\export_memory_footprint.tmp
echo select * from v_section_module_report>> %UT_TMP%\export_memory_footprint.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_memory_footprint.tmp


echo.
echo Exporting Files with QAC or HIS warnings to CSV
echo .headers on> %UT_TMP%\export_files_with_qac_or_his.tmp
echo .mode csv>> %UT_TMP%\export_files_with_qac_or_his.tmp
echo .output %REPORT_PATH_SQL%\\export_files_with_qac_or_his.csv>> %UT_TMP%\export_files_with_qac_or_his.tmp
echo select filename, misra_5 as misra, his from v_q_results>> %UT_TMP%\export_files_with_qac_or_his.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_files_with_qac_or_his.tmp


echo.
echo Exporting Unit Test compiler statistics to CSV
echo .headers on> %UT_TMP%\export_ut_compilerstatistics.tmp
echo .mode csv>> %UT_TMP%\export_ut_compilerstatistics.tmp
echo .output %REPORT_PATH_SQL%\\export_ut_compilerstatistics.csv>> %UT_TMP%\export_ut_compilerstatistics.tmp
echo select project, result from v_ut_results_compiler_statistics>> %UT_TMP%\export_ut_compilerstatistics.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_ut_compilerstatistics.tmp


echo.
echo Exporting Module coverage statistics to CSV
echo .headers on> %UT_TMP%\export_ut_coverage_module.tmp
echo .mode csv>> %UT_TMP%\export_ut_coverage_module.tmp
echo .output %REPORT_PATH_SQL%\\export_ut_coverage_module.csv>> %UT_TMP%\export_ut_coverage_module.tmp
echo select * from v_ut_coverage_module>> %UT_TMP%\export_ut_coverage_module.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_ut_coverage_module.tmp


if exist ..\Config\%CONFIGURATION%_export.bat (
  REM DEBUG: echo EXECUTING ADDITIONAL EXPORT SCRIPTS: ..\Config\%CONFIGURATION%_export.bat
  call ..\Config\%CONFIGURATION%_export.bat
) else (
  REM DEBUG: echo No export extension defined.
)


echo.
echo +++ Export data to Doors Done +++
