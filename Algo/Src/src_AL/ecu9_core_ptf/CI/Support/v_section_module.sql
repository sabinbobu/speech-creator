-- View: v_section_module
DROP VIEW IF EXISTS v_section_module;
CREATE VIEW v_section_module as
select sum(sizedec) as size, module, memory from v_section_module_latest, section_to_memory where
 v_section_module_latest.section=section_to_memory.section
 group by v_section_module_latest.module, memory
 order by module collate nocase, memory;


-- View: v_section_module_helper
DROP VIEW IF EXISTS v_section_module_helper;
CREATE VIEW v_section_module_helper as
select
 m.module,
 max(case when rom.memory = 'ROM' then rom.size end) as ROM,
 max(case when ram.memory = 'RAM' then ram.size end) as RAM
from v_section_module m, v_section_module rom, v_section_module ram
where
 m.module=rom.module and
 m.module=ram.module
group by
 m.module;


-- View: v_section_module_latest
DROP VIEW IF EXISTS v_section_module_latest;
CREATE VIEW v_section_module_latest as 
select compiler_map.*, file_to_module.module from compiler_map, file_to_module where
 githash = (select githash from compiler_map where date = (select max(date) from compiler_map) and
 time = (select max(time) from compiler_map where date = (select max(date) from compiler_map)) ) and
 compiler_map.filename=file_to_module.filename and
 file_to_module.module not null and
 section not like ".debug%";


-- View: v_section_module_report
DROP VIEW IF EXISTS v_section_module_report;
CREATE VIEW v_section_module_report as
select
 module,
 p_ROM as 'Plan ROM', r_ROM as 'Meas ROM', ROM_percent as 'ROM%', iif(ROM_percent<=100,iif(ROM_percent<=85,"OK","WARN"),"OVER") as 'ROM status',
 p_RAM as 'Plan RAM', r_RAM as 'Meas RAM', RAM_percent as 'RAM%', iif(RAM_percent<=100,iif(RAM_percent<=85,"OK","WARN"),"OVER") as 'RAM status'
from (
select
 p.module,
 p.planned_ROM as p_ROM, iif(r.ROM is NULL, 0, r.ROM) as r_ROM, iif(p.planned_ROM=0, iif(r.ROM is NULL, 0, 999), iif(r.ROM is NULL, 0, r.ROM)*100/p.planned_ROM) as ROM_percent,
 p.planned_RAM as p_RAM, iif(r.RAM is NULL, 0, r.RAM) as r_RAM, iif(p.planned_RAM=0, iif(r.RAM is NULL, 0, 999), iif(r.RAM is NULL, 0, r.RAM)*100/p.planned_RAM) as RAM_percent
 from module_size_plan p, v_section_module_helper r where p.module=r.module
)
order by module collate nocase;


-- View: v_section_module_stat
DROP VIEW IF EXISTS v_section_module_stat;
CREATE VIEW v_section_module_stat as
select
 p.module_group as "Group",
 /*sum(p.planned_rom) as "Plan ROM",*/
 iif(sum(r.ROM) is NULL, 0, sum(r.ROM)) as "Meas ROM",
 /*sum(p.planned_ram) as "Plan RAM",*/
 iif(sum(r.RAM) is NULL, 0, sum(r.RAM)) as "Meas RAM"
 from module_size_plan p, v_section_module_helper r where p.module=r.module
group by p.module_group
order by p.module_group collate nocase;


-- View: v_section_module_sum
DROP VIEW IF EXISTS v_section_module_sum;
CREATE VIEW v_section_module_sum as
select
 "** TOTALS **" as "Group",
 sum(r.ROM) as "Meas ROM",
 sum(r.RAM) as "Meas RAM"
 from module_size_plan p, v_section_module_helper r where p.module=r.module;


-- View: v_section_module_percent
DROP VIEW IF EXISTS v_section_module_percent;
CREATE VIEW v_section_module_percent as
select
 "** USAGE **" as "Group",
 printf("%.1f%", 1.0*"Meas ROM"/(select max_rom from config)*100) as "Meas ROM",
 printf("%.1f%", 1.0*"Meas RAM"/(select max_ram from config)*100) as "Meas RAM"
 from v_section_module_sum;


-- View: v_section_module_max
DROP VIEW IF EXISTS v_section_module_max;
CREATE VIEW v_section_module_max as
select
 "** MAXIMUM **" as "Group",
 (select max_rom from config) as "Meas ROM",
 (select max_ram from config) as "Meas RAM";


-- View: v_section_module_aggregate_stat
DROP VIEW IF EXISTS v_section_module_aggregate_stat;
CREATE VIEW v_section_module_aggregate_stat as
WITH StatusCounts AS (
    SELECT
        SUM(CASE WHEN "ROM STATUS"="OK" AND "RAM STATUS"="OK" THEN 1 ELSE 0 END) AS OK_MODULES,
        SUM(CASE WHEN "ROM STATUS"="WARN" OR "RAM STATUS"="WARN" THEN 1 ELSE 0 END) AS WARN_MODULES,
        SUM(CASE WHEN "ROM STATUS"="OVER" OR "RAM STATUS"="OVER" THEN 1 ELSE 0 END) AS OVER_MODULES,
        COUNT(*) AS TotalModules
    FROM
        v_section_module_report
)
SELECT 
    OK_MODULES ||"/"|| TotalModules || " (" || ROUND((OK_MODULES * 1.0 / TotalModules) * 100, 0) || "%) Modules are OK" || CHAR(10) ||
    WARN_MODULES || "/" || TotalModules || " (" || ROUND((WARN_MODULES * 1.0 / TotalModules) * 100, 0) || "%) Modules are WARN" || CHAR(10) ||
    OVER_MODULES || "/" || TotalModules || " (" || ROUND((OVER_MODULES * 1.0 / TotalModules) * 100, 0) || "%) Modules are OVER" AS Combined_Status
FROM
    StatusCounts;
