@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Group memory footprint ***
%DB_TOOL% %DB% < v_section_module_tricoretasking.sql
echo select ".width", max(max(length("Group")+2),12), "-8 -8" from v_section_module_stat; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\v_section_module_stat.tmp
echo .headers on>> %UT_TMP%\v_section_module_stat.tmp
echo .mode column>> %UT_TMP%\v_section_module_stat.tmp

echo select * from v_section_module_stat;>> %UT_TMP%\v_section_module_stat.tmp

echo .headers off>> %UT_TMP%\v_section_module_stat.tmp
echo select * from v_section_module_sum;>> %UT_TMP%\v_section_module_stat.tmp

%DB_TOOL% %DB% < %UT_TMP%\v_section_module_stat.tmp


echo.
echo *** Module memory footprint ***
echo Status based on percent: 0-85 OK, 86-100 WARN, 100+ OVER
echo select ".width", max(length(module)), "-8 -8 -5 10 -8 -8 -5 10" from v_section_module; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\v_section_module.tmp
echo .headers on>> %UT_TMP%\v_section_module.tmp
echo .mode column>> %UT_TMP%\v_section_module.tmp

rem echo select size, module, memory from v_section_module;>> %UT_TMP%\v_section_module.tmp
echo select * from v_section_module_report;>> %UT_TMP%\v_section_module.tmp

%DB_TOOL% %DB% < %UT_TMP%\v_section_module.tmp
