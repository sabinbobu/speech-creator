/* Mother table (compiler_results) is recreated at every test run, so date+time is not needed in the select FROM clause */
-- This is a special case for the Tasking tricore compiler.
-- Here the correct error message is present, no need to attach an additional table (error_msg)

-- View: v_compiler_results_al
DROP VIEW IF EXISTS v_compiler_results_al;
CREATE VIEW v_compiler_results_al as select filename, line, type, error_id as error_text from compiler_results where filename like "Src_AL%" order by filename, line;


-- View: v_compiler_results_n_al
DROP VIEW IF EXISTS v_compiler_results_n_al;
CREATE VIEW v_compiler_results_n_al as select filename, line, type, error_id as error_text from compiler_results where filename not like "Src_AL%" order by filename, line;
