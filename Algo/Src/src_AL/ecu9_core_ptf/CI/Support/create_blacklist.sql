--
-- File generated with SQLiteStudio v3.2.1 on Di Okt 15 16:05:54 2019
--
-- Text encoding used: System
--

-- Table: ut_coverage_blacklist
DROP TABLE IF EXISTS ut_coverage_blacklist;
CREATE TABLE IF NOT EXISTS ut_coverage_blacklist (platform, project, function_name, UNIQUE (platform, project, function_name) ON CONFLICT IGNORE );
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_Init');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_Config');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_Statemachine_ExecState1');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_Statemachine_ExecState2');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_Statemachine');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_Init_SetControl');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExample_VoltageGet');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'SwcExample_Init');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'SwcExample_Config');

--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_Config');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_Init');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_Init_SetControl');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_Statemachine');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_Statemachine_ExecState1');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_Statemachine_ExecState2');
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'F0Bw16_App_default', 'CddExampleCpp_VoltageGet');

--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'Mt_CddExample', NULL);
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'Mt_CddExampleCpp', NULL);
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'Mt_SwcExample', NULL);
--INSERT INTO ut_coverage_blacklist (platform, project, function_name) VALUES ('Asr6', 'Mt_CddAdc', NULL);


-- Table: ut_results_blacklist
DROP TABLE IF EXISTS ut_results_blacklist;
CREATE TABLE IF NOT EXISTS ut_results_blacklist (platform, project, type, name, UNIQUE (platform, project, type, name) ON CONFLICT IGNORE );
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Integration', 'It_SwcExample_Config');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Integration', 'It_SwcExample_Init');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample_Config');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample_Init');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample_Init_SetControl');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample_Statemachine');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample_Statemachine_ExecState1');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample_Statemachine_ExecState2');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_SwcExample_Config');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_SwcExample_Init');

--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Integration', 'It_SwcExample');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExample');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_SwcExample');

--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp_Config');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp_Init');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp_Init_SetControl');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp_Statemachine');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp_Statemachine_ExecState1');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddExampleCpp_Statemachine_ExecState2');

--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddAdc');
--INSERT INTO ut_results_blacklist (platform, project, type, name) VALUES ('Asr6', 'F0Bw16_App_default', 'Unit', 'Mt_CddAdc_Dummy');


-- Table: file_to_module_blacklist
DROP TABLE IF EXISTS file_to_module_blacklist;
CREATE TABLE file_to_module_blacklist (filename);
--INSERT INTO file_to_module_blacklist (filename) VALUES ('<C++ ctors and dtors>');
--INSERT INTO file_to_module_blacklist (filename) VALUES ('<commons>');
--INSERT INTO file_to_module_blacklist (filename) VALUES ('<Linker supplemental gstack info>');

