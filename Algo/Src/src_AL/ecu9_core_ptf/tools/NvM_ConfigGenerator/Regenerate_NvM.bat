@echo off
setlocal

pushd "%~dp0..\.." || (
    echo ERROR: Could not locate the repository root.
    goto :failed
)

where py >nul 2>nul
if errorlevel 1 (
    echo ERROR: Python launcher "py" was not found. Install Python with the Windows launcher.
    popd
    goto :failed
)

py -3 "tools\NvM_ConfigGenerator\generate_nvm_config.py" ^
    --config "tools\NvM_ConfigGenerator\config\NvM.yaml" ^
    --output "Src\config_AL\Al\Al077\bsw\NvM"
set "RESULT=%ERRORLEVEL%"
popd

if not "%RESULT%"=="0" goto :failed
echo NvM configuration regenerated successfully.
goto :done

:failed
set "RESULT=1"
echo NvM configuration regeneration failed.

:done
if /i not "%~1"=="--no-pause" pause
exit /b %RESULT%
