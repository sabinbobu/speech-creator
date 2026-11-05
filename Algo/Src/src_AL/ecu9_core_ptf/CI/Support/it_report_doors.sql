select type, name, lower(result), githash from ut_results where
 lower(type)="integration" and
 githash = (select githash from ut_results where date = (select max(date) from ut_results) and
 time = (select max(time) from ut_results where date = (select max(date) from ut_results)) ) and
 name not in (select name from ut_results_blacklist)
 order by name;
