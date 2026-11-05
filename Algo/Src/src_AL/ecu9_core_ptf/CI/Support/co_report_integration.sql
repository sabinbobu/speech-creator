-- View: v_ut_coverage
DROP VIEW IF EXISTS v_ut_coverage;
CREATE VIEW v_ut_coverage as
SELECT 
    project,
    SUM(COALESCE(C0_percent, 0)) AS C0_percent,
    SUM(COALESCE(C1_percent, 0)) AS C1_percent
FROM 
    v_ut_coverage_latest
WHERE
 function_name!='*module_statistics'
GROUP BY 
project;


-- View: v_ut_coverage_latest
DROP VIEW IF EXISTS v_ut_coverage_latest;
CREATE VIEW v_ut_coverage_latest as
select project, function_name, C0_percent, C0_tested_lines, C0_testable_lines, C1_percent, C1_tested_lines, C1_testable_lines
from ut_coverage where
 githash = (select githash from ut_coverage where date = (select max(date) from ut_coverage) and
 time = (select max(time) from ut_coverage where date = (select max(date) from ut_coverage)) ) and
 function_name not in (select function_name from ut_coverage_blacklist where function_name not NULL)
 order by C0_percent DESC, C1_percent DESC, function_name collate nocase;


-- View: v_ut_coverage_module
DROP VIEW IF EXISTS v_ut_coverage_module;
CREATE VIEW v_ut_coverage_module as
select project as 'Project', 
SUM(COALESCE(C0_tested_lines, 0)) AS 'C0 tested',
SUM(COALESCE(C0_testable_lines, 0)) AS 'C0 testable',
SUM(COALESCE(C0_percent, 0)) AS 'C0 percent',
SUM(COALESCE(C1_tested_lines, 0)) AS 'C1 tested',
SUM(COALESCE(C1_testable_lines, 0)) AS 'C1 testable',
SUM(COALESCE(C1_percent, 0)) AS 'C1 percent'
from v_ut_coverage_latest where
project not in (select project from ut_coverage_blacklist where function_name is NULL)
group by project;
