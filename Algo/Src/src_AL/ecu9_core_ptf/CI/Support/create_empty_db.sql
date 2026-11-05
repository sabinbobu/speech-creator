--
-- File generated with SQLiteStudio v3.2.1 on Do Mai 20 14:07:22 2021
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: compiler_map
DROP TABLE IF EXISTS compiler_map;
CREATE TABLE compiler_map (platform, project, githash, date, time, originhex, origindec INT, sizehex, sizedec INT, section, filename);

-- Table: compiler_results
DROP TABLE IF EXISTS compiler_results;
CREATE TABLE compiler_results (platform, project, githash, date, time, filename, line INTEGER, type, error_id, error_num INTEGER, UNIQUE ( platform, project, githash, date, time, filename, line, type, error_id ) ON CONFLICT IGNORE);

-- Table: error_msg
-- DROP TABLE IF EXISTS error_msg;
CREATE TABLE IF NOT EXISTS error_msg (compiler, error_num integer, error_text);

-- Table: file_to_module
DROP TABLE IF EXISTS file_to_module;
CREATE TABLE file_to_module (filename UNIQUE ON CONFLICT IGNORE COLLATE NOCASE, module);

-- Table: file_to_module_blacklist
DROP TABLE IF EXISTS file_to_module_blacklist;
CREATE TABLE file_to_module_blacklist (filename);

-- Table: link_result
DROP TABLE IF EXISTS link_result;
CREATE TABLE link_result (inFile, in_Section, in_Section_ID, in_Size_MAU_HEX, in_Size_MAU_DEC INT, out_Offset, out_Section, out_Section_ID, out_Size_MAU_HEX, out_Size_MAU_DEC INT);

-- Table: locate_result
DROP TABLE IF EXISTS locate_result;
CREATE TABLE locate_result (Chip, Group_name, Section, Section_ID, Size_MAU_HEX, Size_DEC, Space_addr_HEX, Space_addr_DEC, Chip_addr_HEX, Chip_addr_DEC TEXT, Alignment TEXT);

-- Table: module_size_plan
DROP TABLE IF EXISTS module_size_plan;
CREATE TABLE module_size_plan (module UNIQUE ON CONFLICT IGNORE COLLATE NOCASE NOT NULL ON CONFLICT IGNORE, module_group, planned_rom int, planned_ram int);

-- Table: q_results
DROP TABLE IF EXISTS q_results;
CREATE TABLE q_results (platform, project, tool, githash, date, time, filename, misra_0, misra_1, misra_2, misra_3, misra_4, misra_5, misra_6, misra_7, misra_8, misra_9, his, UNIQUE ( githash, filename ) ON CONFLICT IGNORE);

-- Table: section_to_memory
DROP TABLE IF EXISTS section_to_memory;
--CREATE TABLE section_to_memory (section UNIQUE ON CONFLICT IGNORE COLLATE NOCASE, memory);
CREATE TABLE section_to_memory (section UNIQUE ON CONFLICT IGNORE, memory);
--CREATE TABLE section_to_memory (section, memory);

-- Table: section_to_memory
DROP TABLE IF EXISTS section_to_memory2;
--CREATE TABLE section_to_memory2 (section UNIQUE ON CONFLICT IGNORE COLLATE NOCASE, memory);
--CREATE TABLE section_to_memory2 (section UNIQUE ON CONFLICT IGNORE, memory);
CREATE TABLE section_to_memory2 (section, memory);

-- Table: ut_coverage
DROP TABLE IF EXISTS ut_coverage;
CREATE TABLE ut_coverage (platform, project, tool, githash, date, time, C0_percent INTEGER, C0_tested_lines INTEGER, C0_testable_lines INTEGER, C1_percent INTEGER, C1_tested_lines INTEGER, C1_testable_lines INTEGER, C2_percent INTEGER, C2_tested_lines INTEGER, C2_testable_lines INTEGER, function_name);

-- Table: ut_coverage_blacklist
DROP TABLE IF EXISTS ut_coverage_blacklist;
CREATE TABLE ut_coverage_blacklist (platform, project, function_name, UNIQUE ( platform, project, function_name ) ON CONFLICT IGNORE);

-- Table: ut_results
DROP TABLE IF EXISTS ut_results;
CREATE TABLE ut_results (platform, project, tool, githash, date, time, type, name, result, UNIQUE ( githash, name ) ON CONFLICT IGNORE);

-- Table: ut_results_blacklist
DROP TABLE IF EXISTS ut_results_blacklist;
CREATE TABLE ut_results_blacklist (platform, project, type, name, UNIQUE ( platform, project, type, name ) ON CONFLICT IGNORE);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;

VACUUM;
