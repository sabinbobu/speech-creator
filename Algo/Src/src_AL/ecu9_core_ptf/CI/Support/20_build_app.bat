@echo off
SETLOCAL
call ..\Config\settings.bat

rem Build main app
cd ..\..\Build\VS
call ..\Build.bat %PAR_ECU% %PAR_MCAL% %PAR_CC% %PAR_TEST% %PAR_COVER% %PAR_CORE% %PAR_PRJ% %PAR_VAR% %PAR_BUILD% %PAR_KEY% %PAR_RULE%
cd ..\..\CI\Support
