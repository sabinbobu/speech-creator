/* Mother table (compiler_results) is recreated at every test run, so date+time is not needed in the select FROM clause */

-- View: v_compiler_results_al
DROP VIEW IF EXISTS v_compiler_results_al;
CREATE VIEW v_compiler_results_al as select filename, line, type, error_id, error_text from compiler_results left join error_msg on compiler_results.error_num = error_msg.error_num where filename like "Src_AL%" order by filename, line;


-- View: v_compiler_results_n_al
DROP VIEW IF EXISTS v_compiler_results_n_al;
CREATE VIEW v_compiler_results_n_al as select filename, line, type, error_id, error_text from compiler_results left join error_msg on compiler_results.error_num = error_msg.error_num where filename not like "Src_AL%" order by filename, line;
