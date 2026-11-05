
echo.
echo Exporting DEBUG DATA to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\debug_v_section_module_latest.csv>> %UT_TMP%\export_DEBUG.tmp
echo select * from v_section_module_latest;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


echo.
echo Exporting DEBUG DATA to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\debug_v_section_module_helper.csv>> %UT_TMP%\export_DEBUG.tmp
echo select * from v_section_module_helper;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


echo.
echo Exporting DEBUG DATA to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\debug_v_section_module.csv>> %UT_TMP%\export_DEBUG.tmp
echo select * from v_section_module;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


rem echo.
rem echo Exporting DEBUG DATA to CSV
rem echo .headers on> %UT_TMP%\export_DEBUG.tmp
rem echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
rem echo .output %REPORT_PATH_SQL%\\debug_link_result.csv>> %UT_TMP%\export_DEBUG.tmp
rem echo select * from link_result;>> %UT_TMP%\export_DEBUG.tmp
rem %DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


echo.
echo Exporting DEBUG DATA to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\debug_locate_result.csv>> %UT_TMP%\export_DEBUG.tmp
echo select * from locate_result;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


echo.
echo Exporting Update file to module config to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\NEW_file_to_module.csv>> %UT_TMP%\export_DEBUG.tmp
echo select * from file_to_module order by 1 collate nocase;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


echo.
echo Exporting Update section to memory config to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\NEW_section_to_memory.csv>> %UT_TMP%\export_DEBUG.tmp
echo select * from section_to_memory order by 1 collate nocase;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp


echo.
echo Exporting Update module memory footprint config to CSV
echo .headers on> %UT_TMP%\export_DEBUG.tmp
echo .mode csv>> %UT_TMP%\export_DEBUG.tmp
echo .output %REPORT_PATH_SQL%\\NEW_module_size_plan.csv>> %UT_TMP%\export_DEBUG.tmp
echo select p.module, p.module_group, cast(v."Meas ROM"*1.2+1 as integer) as planned_rom, cast(v."Meas RAM"*1.2+1 as integer) as planned_ram from v_section_module_report as v, module_size_plan as p where v.module==p.module order by p.module;>> %UT_TMP%\export_DEBUG.tmp
%DB_TOOL% %DB% < %UT_TMP%\export_DEBUG.tmp
