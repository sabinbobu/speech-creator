@echo off
SETLOCAL
cls
call ..\Config\settings.bat

if exist %BUILD_BIN_PATH%       rmdir /S /Q %BUILD_BIN_PATH%
if exist ..\..\Build\Tmp        rmdir /S /Q ..\..\Build\Tmp
if exist ..\..\Build\VS\obj     rmdir /S /Q ..\..\Build\VS\obj
if exist *.bak del *.bak
if exist *.tmp del *.tmp
if exist %UT_TMP%\*             del /S /Q %UT_TMP%\*
if exist %REPORT_PATH%\*.csv    del /S /Q %REPORT_PATH%\*.csv
if exist %SINGLE_FILE_REPORT%   del /S /Q %SINGLE_FILE_REPORT%
