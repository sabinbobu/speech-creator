insert into compiler_map (platform, project, githash, date, time, originhex, origindec, sizehex, sizedec, section, filename)
select * from (select platform, project, githash, date, time from compiler_map limit 1), (select
 Space_addr_HEX as originhex, Space_addr_DEC as origindec, Size_MAU_HEX as sizehex, Size_DEC as sizedec, section, section as filename
 from locate_result where section not in (select section from compiler_map) and (substr(section,1,1)='[' is not true) order by section collate nocase);
