@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ Running test Compiler warning report Start +++

rem Set defaults
SET PROJECT_NAME=%MAIN_APP_NAME%
SET INPUT_FILE=%ERROR_LIST_PATH%\%MAIN_APP_NAME%_all.txt
SET OUTPUT_FILE=%ERROR_LIST_PATH%\%MAIN_APP_NAME%_all.sql

FOR /F %%I IN ('git rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I

if exist %INPUT_FILE% del %INPUT_FILE%
for %%a in (%ERROR_LIST_PATH%\*.err) do (
  type "%%a" >> "%INPUT_FILE%"
)

rem echo %INPUT_FILE%

%TEST_RESULT_PARSER_TOOL% --input=%INPUT_FILE% --output=%OUTPUT_FILE% --platform=%PLATFORM_NAME% --project_name=%PROJECT_NAME% --test_type=Unit --parser_type=%WARNING_PARSER_TYPE% --hash_value=%GIT_COMMIT_HASH_VALUE%

echo.
echo +++ Feeding the DB with Compiler warning report data +++

%DB_TOOL% %DB% < %OUTPUT_FILE%

echo.
echo +++ Running test Compiler warning report Done +++
