-- View: v_co_report_integraton_check
DROP VIEW IF EXISTS v_co_report_integraton_check;
CREATE VIEW v_co_report_integraton_check as
select platform, project1, tool, C0_percent, C0_tested_lines, C0_testable_lines, C1_percent, C1_tested_lines, C1_testable_lines, function_name, (C0_testable_lines-control_C0_testable_lines) as diff_C0, (C1_testable_lines-control_C1_testable_lines) as diff_C1 from
(
select * from 
(
select platform, project as project1, tool, githash, date, time, C0_percent, C0_tested_lines, C0_testable_lines, C1_percent, C1_tested_lines, C1_testable_lines, function_name
from ut_coverage where function_name="*module_statistics" and
 githash = (select githash from ut_coverage where date = (select max(date) from ut_coverage) and
 time = (select max(time) from ut_coverage where date = (select max(date) from ut_coverage)) )
 and project not in (select project from ut_coverage_blacklist)
 order by project
),
(
select project as project2, sum(C0_testable_lines) as control_C0_testable_lines from ut_coverage where function_name!="*module_statistics" and
 githash = (select githash from ut_coverage where date = (select max(date) from ut_coverage) and
 time = (select max(time) from ut_coverage where date = (select max(date) from ut_coverage)) )
 and project not in (select project from ut_coverage_blacklist)
 group by project
 order by project
),
(
select project as project3, sum(C1_testable_lines) as control_C1_testable_lines from ut_coverage where function_name!="*module_statistics" and
 githash = (select githash from ut_coverage where date = (select max(date) from ut_coverage) and
 time = (select max(time) from ut_coverage where date = (select max(date) from ut_coverage)) )
 and project not in (select project from ut_coverage_blacklist)
 group by project
 order by project
)
where project1=project2 and project1=project3
);
