@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Memory size report ***

if exist %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%_Size_report.txt (
  type %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%_Size_report.txt
) else (
  type %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%_Size.txt
)
