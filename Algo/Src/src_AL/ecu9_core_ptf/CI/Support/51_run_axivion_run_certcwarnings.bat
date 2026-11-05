@echo off
call ..\Config\settings.bat
SETLOCAL
SET TMP_DIR=..\Tmp

echo.
echo *** AXIVION CERTC Warnings Start ***

if exist %TMP_DIR%\AXN_CertCWarnings.txt (
%PYTHON3% certCwarning.py -w %TMP_DIR%\AXN_CertCWarnings.txt -t certCTemplate.txt -o %TMP_DIR%\AXN_CertCReport.txt
)

if %ERRORLEVEL% equ 0 (
    type "%TMP_DIR%\AXN_CertCReport.txt"
) else (
    echo certCwarning.py python script ended with an error, exit code was %ERRORLEVEL%.
)
endlocal

echo *** AXIVION CERTC Warnings Stop ***