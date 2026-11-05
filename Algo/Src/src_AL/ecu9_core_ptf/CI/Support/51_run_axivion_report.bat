@echo off
SETLOCAL
call ..\Config\settings.bat
SET TMP_DIR=..\Tmp

set OBJ_FILE=..\..\Build\Tmp\Z03In005_App_Axivion\obj\_object_files.txt
if not exist "%OBJ_FILE%" (
  echo [ERROR] could not find the file : %OBJ_FILE%
)
echo.
echo.
for /f %%C in ('findstr /R "^." "%OBJ_FILE%" ^| find /C /V ""') do set FILE_COUNT=%%C
echo ++++++++++++++++++++++++++++++++++++++++++++++++++
echo Total files analyzed by AXIVION: %FILE_COUNT%
echo ++++++++++++++++++++++++++++++++++++++++++++++++++
echo.
echo *** Files with MISRA or HIS warnings ***
%DB_TOOL% %DB% < q_report_integration.sql
echo select ".width", max(length(filename)), "-7 -7 -7 -7 -7 -7 -7 -7 -7 -7 -7" from v_q_results; | %DB_TOOL% -separator " " %DB% > %UT_TMP%\q_report_integration.tmp
echo .headers on>> %UT_TMP%\q_report_integration.tmp
echo .mode column>> %UT_TMP%\q_report_integration.tmp
rem echo select filename, iif(misra_0="0", ".", misra_0) as misra_0, iif(misra_1="0", ".", misra_1) as misra_1, iif(misra_2="0", ".", misra_2) as misra_2, iif(misra_3="0", ".", misra_3) as misra_3, iif(misra_4="0", ".", misra_4) as misra_4, iif(misra_5="0", ".", misra_5) as misra_5, iif(misra_6="0", ".", misra_6) as misra_6, iif(misra_7="0", ".", misra_7) as misra_7, iif(misra_8="0", ".", misra_8) as misra_8, iif(misra_9="0", ".", misra_9) as misra_9, iif(his="0", ".", his) as his from v_q_results;>> %UT_TMP%\q_report_integration.tmp
echo select filename, iif(misra_5="0", "-", misra_5) as misra, iif(his="0", "-", his) as his from v_q_results order by cast(misra_5 AS INT) desc;>> %UT_TMP%\q_report_integration.tmp
rem echo select filename, misra_0, misra_1, misra_2, misra_3, misra_4, misra_5, misra_6, misra_7, misra_8, misra_9, his from v_q_results;>> %UT_TMP%\q_report_integration.tmp

echo select "" as "", sum(misra_5) as "", sum(his) as "" from v_q_results;>> %UT_TMP%\q_report_integration.tmp

FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select printf('Count of files with warnings: %%5d', count(*) ) from v_q_results;"`) DO SET COUNT_FILES_QAC_WARNINGS=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select printf('Total of 0 - 4 warnings:      %%5d', sum(misra_0) + sum(misra_1) + sum(misra_2) + sum(misra_3) + sum(misra_4) ) as total_0_4 from v_q_results;"`) DO SET TOTAL_0_4_WARNINGS=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select printf('Total of 5 - 9 warnings:      %%5d', sum(misra_5) + sum(misra_6) + sum(misra_7) + sum(misra_8) + sum(misra_9) ) as total_5_9 from v_q_results;"`) DO SET TOTAL_5_9_WARNINGS=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select printf('Total of HIS warnings:        %%5d', sum(his) ) as total_his from v_q_results;"`) DO SET TOTAL_HIS_WARNINGS=%%F
FOR /F "tokens=* USEBACKQ" %%F IN (`%DB_TOOL% %DB% "select printf('Warnings grand total:         %%5d', sum(misra_0) + sum(misra_1) + sum(misra_2) + sum(misra_3) + sum(misra_4) + sum(misra_5) + sum(misra_6) + sum(misra_7) + sum(misra_8) + sum(misra_9) + sum(his) ) as grand_total from v_q_results;"`) DO SET GRAND_TOTAL_WARNINGS=%%F
echo %COUNT_FILES_QAC_WARNINGS%
echo %TOTAL_0_4_WARNINGS%
echo %TOTAL_5_9_WARNINGS%
echo %TOTAL_HIS_WARNINGS%
echo %GRAND_TOTAL_WARNINGS%

%DB_TOOL% %DB% < %UT_TMP%\q_report_integration.tmp

echo.

echo *** HIS Deviation Report ***
%PYTHON3% HISwarning.py -w %TMP_DIR%\AXN_HISWarnings.txt -o %TMP_DIR%\AXN_HIS_Report.txt

if exist %TMP_DIR%\AXN_HIS_Report.txt (
	echo.
	type %TMP_DIR%\AXN_HIS_Report.txt
)

 echo *** MISRA Deviation Report ***
 %PYTHON3% MISRAwarning.py -w %TMP_DIR%\AXN_MisraWarnings.txt -o %TMP_DIR%\AXN_MISRA_Report.txt
 if exist %TMP_DIR%\AXN_MISRA_Report.txt (
    echo.
    type %TMP_DIR%\AXN_MISRA_Report.txt
)
