@echo off
SETLOCAL
call ..\Config\settings.bat

REM check if build output hex file exists
set buildOutput=%BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_NAME%_All.hex


if not exist %buildOutput% (
  echo %buildOutput% does not exist! Build error?
  exit /b 1
) else (
  echo %buildOutput% exists, Build OK.
  rem fall thru, so the second step can do its check.
  rem exit /b 0
)


REM check if additional package output exists
set packageOutput=%BUILD_BIN_PATH%\%MAIN_APP_NAME%\%MAIN_APP_PACKAGE_NAME%

IF "%MAIN_APP_PACKAGE_NAME%" == "" (
  echo Delivery package not defined, skipping check.
) else (

  if not exist %packageOutput% (
    echo %packageOutput% does not exist! Package-build error?
    exit /b 1
  ) else (
    FOR /F %%I IN ('dir /b %packageOutput%') DO echo %BUILD_BIN_PATH%\%MAIN_APP_NAME%\%%I exists, Package-build OK.
    exit /b 0
  )

)
