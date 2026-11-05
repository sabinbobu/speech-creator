-- View: v_ut_report_doors
DROP VIEW IF EXISTS v_ut_report_doors;
CREATE VIEW v_ut_report_doors as
select type, name, lower(result) as result, githash from ut_results where
 lower(type)="unit" and
 githash = (select githash from ut_results where date = (select max(date) from ut_results) and
 time = (select max(time) from ut_results where date = (select max(date) from ut_results)) ) and
 name not in (select name from ut_results_blacklist)
 order by name;
