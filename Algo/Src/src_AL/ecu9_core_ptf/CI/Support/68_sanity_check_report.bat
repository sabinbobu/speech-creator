@echo off
SETLOCAL
call ..\Config\settings.bat

echo.
echo.
echo *** Sanity check ***

echo.
echo S1. These FILES are found in the generated map file, but NOT found in the file_to_module.csv configuration.
echo ACTION: Add these FILES to the file_to_module.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select distinct filename from compiler_map where compiler_map.filename not in (select filename from file_to_module) and compiler_map.filename not in (select filename from file_to_module_blacklist) order by lower(filename);"

echo.
echo.
echo S2. These FILES are found in the file_to_module.csv configuration, but NOT found in the generated map file.
echo ACTION: Delete these FILES from the file_to_module.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select distinct filename from file_to_module where filename not in (select filename from compiler_map) order by 1;"

echo.
echo.
echo S3. These MODULES are found in the file_to_module.csv configuration, but NOT found in the module_size_plan.csv configuration.
echo ACTION: Add these MODULES to the module_size_plan.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select distinct printf('''%%s''', module) as module from file_to_module where module not in (select module from module_size_plan) order by 1 collate nocase;"

echo.
echo.
echo S4. These MODULES are found in the module_size_plan.csv configuration, but NOT found in the file_to_module.csv configuration.
echo ACTION: Add these MODULES to the file_to_module.csv configuration OR delete these from the module_size_plan.csv.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select distinct printf('''%%s''', module) as module from module_size_plan where module not in (select module from file_to_module) order by 1 collate nocase;"

echo.
echo.
echo S5. These SECTIONS are found in the generated map file, but NOT found in the section_to_memory.csv configuration.
echo ACTION: Add these SECTIONS to the section_to_memory.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select distinct section from compiler_map where section not in (select distinct section from section_to_memory) order by 1 collate nocase;"

echo.
echo.
echo S6. These SECTIONS are found in the section_to_memory.csv, but NOT found in the generated map file.
echo ACTION: Delete these SECTIONS from the section_to_memory.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select distinct section from section_to_memory where section not in (select distinct section from compiler_map) order by 1 collate nocase;"

echo.
echo.
echo S7. These are the duplicates in the section_to_memory.csv configuration.
echo ACTION: Delete these duplicate entries from the section_to_memory.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select section, count(*) as count from (select section from section_to_memory2) group by section having count > 1 order by 1 collate nocase;"

echo.
echo.
echo S8. These items have no valid memory defined in the section_to_memory.csv configuration.
echo ACTION: Edit the memory field in the section_to_memory.csv configuration.
echo -------------------------------------------------------------------------------
%DB_TOOL% %DB% "select section, memory from section_to_memory where memory=='' or memory=='UNKNOWN' order by 1 collate nocase;"
