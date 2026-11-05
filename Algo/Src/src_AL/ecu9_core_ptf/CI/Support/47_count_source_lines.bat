@echo off
SETLOCAL

call ..\Config\settings.bat

echo.
echo.

rem echo.
rem echo +++ 47_count_source_lines: start +++

:: Set the path variable
set "MY_PATH=..\..\Src\Src_AL"
:: Execute PowerShell command within a batch file
powershell -NoProfile -Command ^
    "$extensions = @('*.c', '*.cpp', '*.h', '*.hpp');" ^
    "$excludePattern = 'Src_ThirdParty';" ^
    "$totalLines = 0;" ^
    "$totalFiles = 0;" ^
    "foreach ($ext in $extensions) {" ^
    "    Get-ChildItem -Path '%MY_PATH%' -Recurse -Filter $ext | Where-Object { $_.FullName -notmatch $excludePattern } | ForEach-Object {" ^
    "        $wcOutput = & '%WC%' -l $_.FullName;" ^
    "        if ($wcOutput -match '^\s*(\d+)\s+.*$') {" ^
    "            $lines = [int]$matches[1];" ^
    "            $totalLines += $lines;" ^
    "            $totalFiles += 1;" ^
    "        }" ^
    "    }" ^
    "}" ^
    "Write-Output ('===========================' + [Environment]::NewLine + 'Summary of Source Files' + [Environment]::NewLine + '===========================' + [Environment]::NewLine);" ^
    "Write-Output ('Total Files Processed: ' + $totalFiles);" ^
    "Write-Output ('Total Lines Counted:   ' + $totalLines);" ^
    "Write-Output '===========================';"

endlocal
rem echo +++ 47_count_source_lines: Done +++