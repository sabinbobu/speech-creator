REM %PATH_TOOLSGENERIC% is a variable which can be set from outside (e.g. in Windows or in a Jenkinsfile)
REM %TOOLSGENERIC_PATH% is a variable used internally in the CI\Support scripts
REM if %PATH_TOOLSGENERIC% is not set, use default "..\..\..\toolsgeneric"
SET TOOLSGENERIC_PATH=%PATH_TOOLSGENERIC%
if "%PATH_TOOLSGENERIC%X"=="X" set TOOLSGENERIC_PATH=..\..\..\toolsgeneric

SET DB=..\db\nightly.sqlite3
SET DB_TOOL=%TOOLSGENERIC_PATH%\Utilities\CommonDomain\sqlite\sqlite3.exe
SET TEST_RESULT_PARSER_TOOL=%TOOLSGENERIC_PATH%\Utilities\AL\ALTestResult\ALTestResult.exe
SET GIT=git
SET PYTHON=%TOOLSGENERIC_PATH%\Utilities\CommonDomain\python\python27\python.exe

rem TAILOR
SET PAR_ECU=Z03
SET PAR_MCAL=STM32_F4
SET PAR_CC=ARM_GCC
SET PAR_TEST=CUnit
SET PAR_COVER=CTC
SET PAR_CORE=M4F
SET PAR_PRJ=In005
SET PAR_VAR=App
SET PAR_BUILD=default
SET PAR_KEY=NonKey
SET PAR_RULE=rebuild
SET PAR_RULE_DELIVERY=rebuild_delivery

SET PAR_ECU_UT=W00

SET PLATFORM_NAME=In005
SET MAIN_APP_NAME=%PAR_ECU%%PAR_PRJ%_%PAR_VAR%_%PAR_BUILD%
SET MAIN_APP_PACKAGE_NAME=
SET BUILD_BIN_PATH=..\..\Build\Bin
SET ERROR_LIST_PATH=..\..\Build\Tmp\%MAIN_APP_NAME%\err
SET REPORT_PATH=..\TestResults
SET REPORT_PATH_SQL=..\\TestResults
SET SINGLE_FILE_REPORT=%REPORT_PATH%\SingleFileReport.txt
SET UT_TMP=..\Tmp
SET CONFIG_PATH=..\Config
SET CONFIG_PATH_SQL=..\\Config

if not exist %UT_TMP% (
  md %UT_TMP%
)

if not exist %REPORT_PATH% (
  md %REPORT_PATH%
)
