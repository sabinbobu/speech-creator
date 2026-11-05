@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Code style check ***

echo.
echo C1. These functions are declared with similar names, but there is difference with the upper/lowercase characters.
echo NOTE: items are displayed in lowercase.
echo ACTION: Review and eliminate these entries in the source code to reduce project implementation risk.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select section, count(*) as count from (select lower(section) as section from section_to_memory) group by section having count > 1 order by 1 collate nocase;"
