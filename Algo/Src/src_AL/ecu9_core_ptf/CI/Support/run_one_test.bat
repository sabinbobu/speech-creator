@echo off
SETLOCAL
call ..\Config\settings.bat

rem %1 = CddExample
rem %2 = Unit / Integration
rem %3 = CUnit

echo.
echo +++ Running test: %1 Start +++


FOR /F %%I IN ('%GIT% rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I

cd ..\..\Build\VS
rem call ..\Build.bat %PAR_ECU_UT% PC_WIN32API WIN_GCC %3 %PAR_COVER% X64 %PAR_PRJ% Test Cdd %1 default NonKey rebuild
call     ..\Build.bat %PAR_ECU_UT% PC_WIN32API WIN_GCC %3 %PAR_COVER% X64 %PAR_PRJ% Test %1 NonKey rebuild
cd ..\..\CI\Support

SET FILEPATH=%PAR_ECU_UT%%PAR_PRJ%_Test_%1
SET FILENAME=%PAR_ECU_UT%%PAR_PRJ%_Test_%1_ExecutionResult

set buildOutput=Build\Bin\%FILEPATH%\%FILEPATH%.exe
if not exist ..\..\%buildOutput% (
  echo %buildOutput% does not exist! Build error?
  SET SUCCESS="FATAL"
  REM exit /b 1
) else (
  echo %buildOutput% exists, Build OK.
  SET SUCCESS="OK"
)

echo.
echo +++ Parsing unit test results (Pass/Fail) +++

SET  INFILE_UT=..\..\Build\Bin\%FILEPATH%\%FILENAME%.txt
SET SQLFILE_UT=..\..\Build\Bin\%FILEPATH%\%FILENAME%_%PAR_COVER%.sql
if exist %SQLFILE_UT% del %SQLFILE_UT%

%TEST_RESULT_PARSER_TOOL% --input=%INFILE_UT% --output=%SQLFILE_UT% --platform=%PLATFORM_NAME% --project_name=%1 --test_type=%2 --tool_name=%PAR_COVER% --hash_value=%GIT_COMMIT_HASH_VALUE% --parser_type=PassFail
echo insert into ut_results (platform, project, tool, githash, date, time, type, name, result) values ("%PLATFORM_NAME%", "%1", "Compiler", "%GIT_COMMIT_HASH_VALUE%", date('now'), time('now','+2 hours'), "Statistics", "%1", %SUCCESS%); >> %SQLFILE_UT%

echo.
echo +++ Feeding the DB with PassFail data +++

%DB_TOOL% %DB% < %SQLFILE_UT%

echo.
echo +++ Parsing unit test coverage +++

if "%PAR_COVER%"=="CTC" (
  SET  INFILE_COV=..\..\Build\Bin\%FILEPATH%\CtcProfile.txt
  SET SQLFILE_COV=..\..\Build\Bin\%FILEPATH%\CtcProfile.sql
)
if "%PAR_COVER%"=="SCOV" (
  SET  INFILE_COV=..\..\Build\Bin\%FILEPATH%\GcovHtmlFile\index.html
  SET SQLFILE_COV=..\..\Build\Bin\%FILEPATH%\GcovProfile.sql
)
if "%PAR_COVER%"=="GCOV" (
  SET  INFILE_COV=..\..\Build\Tmp\%FILEPATH%\obj\gcovr_output.txt
  SET SQLFILE_COV=..\..\Build\Bin\%FILEPATH%\GcovProfile.sql
)

IF "%2"=="Unit" (
  if exist %SQLFILE_COV% del %SQLFILE_COV%

  %TEST_RESULT_PARSER_TOOL% --input=%INFILE_COV% --output=%SQLFILE_COV% --platform=%PLATFORM_NAME% --project_name=%1 --test_type=%2 --tool_name=%PAR_COVER% --hash_value=%GIT_COMMIT_HASH_VALUE% --parser_type=%PAR_COVER%_Coverage

  echo.
  echo +++ Feeding the DB with coverage data +++

  %DB_TOOL% %DB% < %SQLFILE_COV%
)

echo.
echo +++ Running test: %1 Done +++
