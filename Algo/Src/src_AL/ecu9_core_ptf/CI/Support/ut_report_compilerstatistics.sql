-- View: v_ut_results_compiler_statistics
DROP VIEW IF EXISTS v_ut_results_compiler_statistics;
CREATE VIEW v_ut_results_compiler_statistics as
select project, tool, type, name, result from ut_results where
 lower(tool)="compiler" and
 lower(type)="statistics" and
 githash = (select githash from ut_results where date = (select max(date) from ut_results) and
 time = (select max(time) from ut_results where date = (select max(date) from ut_results)) ) and
 name not in (select name from ut_results_blacklist)
 order by name collate nocase;
