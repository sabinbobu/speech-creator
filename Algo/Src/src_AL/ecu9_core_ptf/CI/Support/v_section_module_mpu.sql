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
module,
(ROM_U + ROM_T) as ROM, ROM_U, ROM_T,
(RAM_U + RAM_T) as RAM, RAM_U, RAM_T
from
(select
module,
iif(ROM_U is NULL, 0, ROM_U) as ROM_U,
iif(ROM_T is NULL, 0, ROM_T) as ROM_T,
iif(RAM_U is NULL, 0, RAM_U) as RAM_U,
iif(RAM_T is NULL, 0, RAM_T) as RAM_T
from
(select
  m.module,
  max(case when rom.memory = 'ROM' then rom.size end) as ROM_U,
  max(case when rom.memory = 'ROM_T' then rom.size end) as ROM_T,
  max(case when ram.memory = 'RAM' then ram.size end) as RAM_U,
  max(case when ram.memory = 'RAM_T' then ram.size end) as RAM_T
from v_section_module m, v_section_module rom, v_section_module ram
where
  m.module=rom.module and
  m.module=ram.module
group by
  m.module));


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
 p_ROM as 'Plan ROM', r_ROM as 'Meas ROM', r_ROM_U as "M ROM_U", r_ROM_T as "M ROM_T", ROM_percent as 'ROM%',
 iif((substr(module,1,2)=="T_" AND r_ROM_U!=0) OR (substr(module,1,2)=="U_" AND r_ROM_T!=0),"**ERROR**",
 iif(ROM_percent<=100,iif(ROM_percent<=85,"OK","WARN"),"*OVER*") ) as 'ROM status',
 p_RAM as 'Plan RAM', r_RAM as 'Meas RAM', r_RAM_U as "M RAM_U", r_RAM_T as "M RAM_T", RAM_percent as 'RAM%',
 iif((substr(module,1,2)=="T_" AND r_RAM_U!=0) OR (substr(module,1,2)=="U_" AND r_RAM_T!=0),"**ERROR**",
 iif(RAM_percent<=100,iif(RAM_percent<=85,"OK","WARN"),"*OVER*") ) as 'RAM status'
from (
select
 p.module,
 p.planned_rom as p_ROM, r.ROM as r_ROM, r.ROM_U as r_ROM_U, r.ROM_T as r_ROM_T, iif(p.planned_ROM=0, iif(r.ROM is NULL, 0, 999), r.ROM*100/p.planned_rom) as ROM_percent,
 p.planned_ram as p_RAM, r.RAM as r_RAM, r.RAM_U as r_RAM_U, r.RAM_T as r_RAM_T, iif(p.planned_RAM=0, iif(r.RAM is NULL, 0, 999), r.RAM*100/p.planned_ram) as RAM_percent
 from module_size_plan p, v_section_module_helper r where p.module=r.module
)
order by module collate nocase;


-- View: v_section_module_stat
DROP VIEW IF EXISTS v_section_module_stat;
CREATE VIEW v_section_module_stat as
select
 p.module_group as "Group",
 /*sum(p.planned_rom) as "Plan ROM",*/
 sum(r.ROM) as "Meas ROM",
 sum(r.ROM_U) as "ROM_U",
 sum(r.ROM_T) as "ROM_T",
 /*sum(p.planned_ram) as "Plan RAM",*/
 sum(r.RAM) as "Meas RAM",
 sum(r.RAM_U) as "RAM_U",
 sum(r.RAM_T) as "RAM_T"
 from module_size_plan p, v_section_module_helper r where p.module=r.module
group by p.module_group
order by p.module_group collate nocase;


-- View: v_section_module_sum
DROP VIEW IF EXISTS v_section_module_sum;
CREATE VIEW v_section_module_sum as
select
 "** TOTALS **" as "Group",
 sum(r.ROM) as "Meas ROM",
 sum(r.ROM_U) as "ROM_U",
 sum(r.ROM_T) as "ROM_T",
 sum(r.RAM) as "Meas RAM",
 sum(r.RAM_U) as "RAM_U",
 sum(r.RAM_T) as "RAM_T"
 from module_size_plan p, v_section_module_helper r where p.module=r.module;


-- View: v_section_module_sanity
DROP VIEW IF EXISTS v_section_module_sanity;
CREATE VIEW v_section_module_sanity as
select * from(
SELECT originhex, origindec, sizehex, sizedec, compiler_map.section, compiler_map.filename, section_to_memory.memory, file_to_module.module
from compiler_map, section_to_memory, file_to_module
where compiler_map.section=section_to_memory.section
 and compiler_map.filename=file_to_module.filename
 and compiler_map.section not like ".debug%"
) where
 module like "U_%" and memory like "%_T"
OR
 module like "T_%" and memory not like "%_T"
order by /*origindec*/ module, memory, filename collate nocase;
