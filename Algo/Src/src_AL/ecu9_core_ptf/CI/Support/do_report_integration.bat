@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
call ..\Config\settings.bat

SET "SPACES=     "

rem if exist *.tmp del *.tmp
rem if exist %UT_TMP%\*.tmp del %UT_TMP%\*.tmp

echo *** Single file report of project %PLATFORM_HUMAN_NAME% ***
echo.

rem Display the timestamp
call 02_timestamp.bat

echo.
FOR /F %%I IN ('%GIT% rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I
echo git hash: %GIT_COMMIT_HASH_VALUE%


if %OPTION_USE_BUILD_APP% GTR 0 (
  echo.
  echo.
  echo *** Does the target application build? ***
  call 30_eval_app_build_report.bat
)

if %OPTION_USE_WARNING_PARSER%   GTR 0 (
  if %WARNING_PARSER_TYPE% == Warning_Tricore (
    call 40_run_warning_tricoretasking_report.bat
  ) else (
    call 40_run_warning_report.bat
  )
)

if %OPTION_USE_SIZE_ANALYSIS%    GTR 0  call 42_analyze_size_report.bat

if %OPTION_USE_MAP_ANALYSIS%     GTR 0 (
  if %CONFIG_USE_MPU% ==  0 (
    SET MPU_STR=
  ) else (
    SET MPU_STR=_mpu
  )
  if %MAP_PARSER_TYPE% == Map_TricoreTasking (
    SET PARSER_STR=_tricoretasking
  ) else (
    SET PARSER_STR=
  )
  call 45_analyze_map!PARSER_STR!!MPU_STR!_report.bat
)
if %OPTION_USE_LINE_COUNT%             GTR 0  call 47_count_source_lines.bat
if %OPTION_USE_QAC%                    GTR 0  call 50_run_qac_report.bat
if %OPTION_USE_AXIVION%                GTR 0  call 51_run_axivion_report.bat
if %OPTION_USE_UNITTEST_CHECKER%       GTR 0  call 61_run_unit_test_checker_report.bat
if %OPTION_USE_UNITTEST%               GTR 0  call 60_run_all_ut_tests_report.bat
if %OPTION_USE_INTEGRATIONTEST%        GTR 0  call 65_run_all_it_tests_report.bat
if %OPTION_USE_REPORT_SANITYCHECK%     GTR 0  call 68_sanity_check_report.bat
if %OPTION_USE_REPORT_CODESTYLECHECK%  GTR 0  call 69_code_style_check_report.bat

echo.
echo.
echo *** End of Single file report ***
