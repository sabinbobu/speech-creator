@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ Running test QAC Start +++

FOR /F %%I IN ('git rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I

cd ..\..\Build\Tmp\%MAIN_APP_NAME%\qac
call _%MAIN_APP_NAME%_qac_QAC-8.1.2-R_analyze.bat

if OPTION_USE_QAC_HTML == 1 (
  echo.
  echo +++ Create QAC html report Start +++

  call _%MAIN_APP_NAME%_qac_QAC-8.1.2-R_report.bat

  echo.
  echo +++ Create QAC html report Done +++
)

cd ..\..\..\..\CI\Support

SET FILENAME=%MAIN_APP_NAME%_qac_QAC-8.1.2-R_analyze_all

%TEST_RESULT_PARSER_TOOL% --input=%BUILD_BIN_PATH%\%MAIN_APP_NAME%\%FILENAME%.txt --output=%BUILD_BIN_PATH%\%MAIN_APP_NAME%\%FILENAME%.sql --platform=%PLATFORM_NAME% --project_name=%MAIN_APP_NAME% --test_type=Unit --tool_name=QAC --parser_type=QAC --hash_value=%GIT_COMMIT_HASH_VALUE%

echo.
echo +++ Feeding the DB with QAC data +++

%DB_TOOL% %DB% < %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%FILENAME%.sql

echo.
echo +++ Running test QAC Done +++
