-- Table: section_to_memory
DROP TABLE IF EXISTS section_to_memory;
--CREATE TABLE section_to_memory (section UNIQUE ON CONFLICT IGNORE COLLATE NOCASE, memory);
CREATE TABLE section_to_memory (section UNIQUE ON CONFLICT IGNORE, memory);
--CREATE TABLE section_to_memory (section, memory);
