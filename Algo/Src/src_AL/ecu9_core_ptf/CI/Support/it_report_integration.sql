-- View: v_it_results
DROP VIEW IF EXISTS v_it_results;
CREATE VIEW v_it_results as
select type, name, replace(result, "FAILED", "*FAILED*") as result from ut_results where
 lower(type)="integration" and
 githash = (select githash from ut_results where date = (select max(date) from ut_results) and
 time = (select max(time) from ut_results where date = (select max(date) from ut_results)) ) and
 name not in (select name from ut_results_blacklist)
 order by result, name collate nocase;
