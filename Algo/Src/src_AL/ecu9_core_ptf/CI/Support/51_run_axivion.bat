@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo +++ Running test Axivion Start +++

FOR /F %%I IN ('git rev-parse HEAD') DO SET GIT_COMMIT_HASH_VALUE=%%I


cd ..\..\Build\ToolsSpecific\Cust\In\In005\AXIVION
set PATH=%CD%\..\..\..\..\..\..\..\ToolsGeneric\StaticCodeAnalysis\AXIVION\bauhaus-suite-7_8_1-x86_64-windows\bin;%PATH%
set PATH=D:\ALGitRepo\ToolsGeneric\StaticCodeAnalysis\AXIVION\bauhaus-suite-7_8_1-x86_64-windows\bin;%PATH%
call start_analysis.bat
cd ..\..\..\..\..\..\CI\Support


echo.
echo +++ Running test AXIVION Done +++
