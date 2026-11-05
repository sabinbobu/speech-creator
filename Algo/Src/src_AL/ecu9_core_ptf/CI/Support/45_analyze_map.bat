@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ 45_analyze_map: Start +++

rem Set defaults
SET PROJECT_NAME=%MAIN_APP_NAME%

SET MAP_FILE_NAME=%MAIN_APP_NAME%

SET INPUT_FILE=%BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAP_FILE_NAME%.map
SET OUTPUT_FILE=%BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAP_FILE_NAME%.sql

FOR /F %%I IN ('git rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I

%TEST_RESULT_PARSER_TOOL% --input=%INPUT_FILE% --output=%OUTPUT_FILE% --platform=%PLATFORM_NAME% --project_name=%PROJECT_NAME% --test_type=Unit --parser_type=%MAP_PARSER_TYPE% --hash_value=%GIT_COMMIT_HASH_VALUE%

echo.
echo +++ Feeding the DB with Map data +++

%DB_TOOL% %DB% "drop table if exists compiler_map;"
%DB_TOOL% %DB% < %OUTPUT_FILE%

echo.
echo +++ 45_analyze_map: Done +++
