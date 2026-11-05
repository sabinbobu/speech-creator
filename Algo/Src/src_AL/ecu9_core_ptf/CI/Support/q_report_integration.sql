-- View: v_q_results
DROP VIEW IF EXISTS v_q_results;
CREATE VIEW v_q_results as
select filename, misra_0, misra_1, misra_2, misra_3, misra_4, misra_5, misra_6, misra_7, misra_8, misra_9, his
 from q_results where
 githash = (select githash from q_results where date = (select max(date) from q_results) and
 time = (select max(time) from q_results where date = (select max(date) from q_results)) )
 order by filename;
