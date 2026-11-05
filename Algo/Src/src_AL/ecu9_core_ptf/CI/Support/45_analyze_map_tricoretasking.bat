@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ 45_analyze_map_tricoretasking: Start +++

FOR /F %%I IN ('%GIT% rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I

REM %PYTHON3% .\map_parser_LINK_RESULT.py    %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  stdout                             csv  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE% > %UT_TMP%\map_parser_LINK_RESULT_stdout.csv
REM %PYTHON3% .\map_parser_LINK_RESULT.py    %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  %UT_TMP%\map_parser_LINK_RESULT    csv  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE%
REM %PYTHON3% .\map_parser_LINK_RESULT.py    %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  stdout                             sql  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE% > %UT_TMP%\map_parser_LINK_RESULT_stdout.sql
%PYTHON3% .\map_parser_LINK_RESULT.py    %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  %UT_TMP%\map_parser_LINK_RESULT    sql  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE%

REM %PYTHON3% .\map_parser_LOCATE_RESULT.py  %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  stdout                             csv  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE% > %UT_TMP%\map_parser_LOCATE_RESULT_stdout.csv
REM %PYTHON3% .\map_parser_LOCATE_RESULT.py  %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  %UT_TMP%\map_parser_LOCATE_RESULT  csv  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE%
REM %PYTHON3% .\map_parser_LOCATE_RESULT.py  %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  stdout                             sql  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE% > %UT_TMP%\map_parser_LOCATE_RESULT_stdout.sql
%PYTHON3% .\map_parser_LOCATE_RESULT.py  %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%.map  %UT_TMP%\map_parser_LOCATE_RESULT  sql  %PLATFORM_NAME%  %PAR_PRJ%  %GIT_COMMIT_HASH_VALUE%

@rem powershell "c:\users\F79382B\workspace\toolsgeneric\Utilities\CommonDomain\python\python383\python.exe ./map_parser.py | tee map_parser.log"

echo.
echo +++ Feeding the DB with Map data +++

goto SKIP_CSV_IMPORT
if exist %UT_TMP%\import.tmp (
  del %UT_TMP%\import.tmp
)

if exist %UT_TMP%\map_parser_LINK_RESULT.csv (
  echo .mode csv>> %UT_TMP%\import.tmp
  echo .import --skip 1 %UT_TMP_SQL%\\map_parser_LINK_RESULT.csv link_result>> %UT_TMP%\import.tmp
) else (
  echo ERROR file not found: %UT_TMP%\map_parser_LINK_RESULT.csv
  exit /b 1
)

if exist %UT_TMP%\map_parser_LOCATE_RESULT.csv (
  echo .mode csv>> %UT_TMP%\import.tmp
  echo .import --skip 1 %UT_TMP_SQL%\\map_parser_LOCATE_RESULT.csv locate_result>> %UT_TMP%\import.tmp
) else (
  echo ERROR file not found: %UT_TMP%\map_parser_LOCATE_RESULT.csv
  exit /b 1
)

%DB_TOOL% %DB% < %UT_TMP%\import.tmp
:SKIP_CSV_IMPORT

%DB_TOOL% %DB% "drop table if exists compiler_map;"
%DB_TOOL% %DB% "drop table if exists link_result;"
%DB_TOOL% %DB% < %UT_TMP%\map_parser_LINK_RESULT.sql

%DB_TOOL% %DB% "drop table if exists locate_result;"
%DB_TOOL% %DB% < %UT_TMP%\map_parser_LOCATE_RESULT.sql


%DB_TOOL% %DB% < add_LOCATE_RESULT_to_COMPILER_MAP.sql


echo +++ 45_analyze_map_tricoretasking: Done +++
