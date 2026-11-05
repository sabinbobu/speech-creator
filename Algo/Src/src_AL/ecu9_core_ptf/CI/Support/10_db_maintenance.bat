@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ 10_db_maintenance.bat: Start +++

if %OPTION_USE_DB_MAINTENANCE% == 1 (
  %DB_TOOL% %DB% < create_empty_db.sql
)

%DB_TOOL% %DB% < it_report_integration.sql
%DB_TOOL% %DB% < q_report_integration.sql
%DB_TOOL% %DB% < co_report_integration.sql
%DB_TOOL% %DB% < co_report_integration_check.sql
%DB_TOOL% %DB% < ut_report_compilerstatistics.sql
%DB_TOOL% %DB% < ut_report_integration.sql

if %MAP_PARSER_TYPE% == Map_TricoreTasking (
  SET PARSER_STR=_tricoretasking
) else (
  SET PARSER_STR=
)
if %CONFIG_USE_MPU% == 1 (
  SET MPU_STR=_mpu
) else (
  SET MPU_STR=
)
%DB_TOOL% %DB% < v_section_module%PARSER_STR%%MPU_STR%.sql


if "%WARNING_PARSER_TYPE%" == "Warning_Tricore" (
  %DB_TOOL% %DB% < w_report_integration_tricoretasking.sql
) else (
  %DB_TOOL% %DB% < w_report_integration.sql
)

%DB_TOOL% %DB% < create_blacklist.sql

if exist error_list_%PAR_CC%.sql (
  %DB_TOOL% %DB% < error_list_%PAR_CC%.sql
)

REM Load any additional DB extensions
if exist ..\Config\%CONFIGURATION%_db_addition.sql (
  REM DEBUG: echo EXECUTING ADDITIONAL DB SCRIPTS: ..\Config\%CONFIGURATION%_db_addition.sql
  %DB_TOOL% %DB% < ..\Config\%CONFIGURATION%_db_addition.sql
) else (
  REM DEBUG: echo No DB addition defined.
)


REM Finally import the configuration data
if exist %UT_TMP%\create_blacklist.tmp (
  del %UT_TMP%\create_blacklist.tmp
)

echo delete from module_size_plan;>> %UT_TMP%\create_blacklist.tmp
echo .mode csv>> %UT_TMP%\create_blacklist.tmp
echo .import --skip 1 %CONFIG_PATH_SQL%\\module_size_plan.csv module_size_plan>> %UT_TMP%\create_blacklist.tmp

echo delete from file_to_module;>> %UT_TMP%\create_blacklist.tmp
echo .mode csv>> %UT_TMP%\create_blacklist.tmp
echo .import --skip 1 %CONFIG_PATH_SQL%\\file_to_module.csv file_to_module>> %UT_TMP%\create_blacklist.tmp

echo delete from section_to_memory;>> %UT_TMP%\create_blacklist.tmp
echo delete from section_to_memory2;>> %UT_TMP%\create_blacklist.tmp
echo .mode csv>> %UT_TMP%\create_blacklist.tmp
echo .import --skip 1 %CONFIG_PATH_SQL%\\section_to_memory.csv section_to_memory>> %UT_TMP%\create_blacklist.tmp
echo .import --skip 1 %CONFIG_PATH_SQL%\\section_to_memory.csv section_to_memory2>> %UT_TMP%\create_blacklist.tmp

echo DROP TABLE IF EXISTS config;>> %UT_TMP%\create_blacklist.tmp
echo CREATE TABLE config (max_rom, max_ram);>> %UT_TMP%\create_blacklist.tmp
echo INSERT INTO config (max_rom, max_ram) VALUES (%MAX_ROM%, %MAX_RAM%);>> %UT_TMP%\create_blacklist.tmp

%DB_TOOL% %DB% < %UT_TMP%\create_blacklist.tmp


echo +++ 10_db_maintenance.bat: Done +++
