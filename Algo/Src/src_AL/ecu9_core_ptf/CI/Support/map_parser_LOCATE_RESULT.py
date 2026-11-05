import sys
import re
import datetime

DEBUG = False
OPTION_USE_OWN_DATA_STRUCTURE = True

TYPE = "" #original
#TYPE = "_REDUCED"
#TYPE = "_TEST"


if len(sys.argv) != 7:
    print("Parameter error: ", sys.argv[0], "  tricore_tasking.map  output_file  sql|csv  platform  project  githash")
    sys.exit(-1)

if DEBUG:
    OPTION_USE_OUTPUT_FILE   = True #Configure for debugging
    OPTION_OUTPUT_FORMAT_SQL = True #Configure for debugging
    #MAP_FILENAME             = r"c:\Users\f79382b\workspace\hdecua\Build\Bin\In00In000_App_default\In00In000_App_default.map"
    MAP_FILENAME             = r"C:\Users\f79382b\workspace\_python\CI\CI_parse_tricore_map\Support\In00In000_App_default"+ TYPE + ".map"
    OUT_FILEEXT              = "sql" if OPTION_OUTPUT_FORMAT_SQL else "csv"
    OUT_FILENAME             = r"C:\Users\f79382b\workspace\_python\CI\CI_parse_tricore_map\Tmp\map_parser_LINK_RESULT"+ TYPE
    CONFIG_PLATFORM          = "Dlc00"
    CONFIG_PROJECT           = "Dlc00Dl006_App_default"
    CONFIG_GITHASH           = "3cae818b6fe822c5d088eff4da9514a1ec88ede1"
else:
    OUT_FILEEXT              = sys.argv[3].lower() # 'sql' XOR 'csv'
    OPTION_OUTPUT_FORMAT_SQL = (OUT_FILEEXT == 'sql')
    MAP_FILENAME             = sys.argv[1]
    OUT_FILENAME             = sys.argv[2]
    OPTION_USE_OUTPUT_FILE   = (OUT_FILENAME != 'stdout')
    CONFIG_PLATFORM          = sys.argv[4]
    CONFIG_PROJECT           = sys.argv[5]
    CONFIG_GITHASH           = sys.argv[6]


CONFIG_DATE = datetime.datetime.now().strftime("%Y-%m-%d")
CONFIG_TIME = datetime.datetime.now().strftime("%H:%M:%S")

SECTION_HEADER_PATTERN = r"\**  Locate Result  \**"
SECTION_HEADER2_PATTERN = r'\|=+\|'
SECTION_RECORD_PATTERN = r"\| (.*?) \| (.*?) \| (.*?) \| (.*?) \| (.*?) \| (.*?) \| (.*?) \|"
SECTION_BEGIN_OR_END_PATTERN = r"\+-+\+"

found_list = []
list_entry = ['', '', '', '', '', '', '']
linenum = 0

f = open(MAP_FILENAME, 'r')
for line in f:
    linenum += 1
    if re.search(SECTION_HEADER_PATTERN, line):
        break

for line in f:
    linenum += 1
    if re.search(SECTION_HEADER2_PATTERN, line):
        break

#if DEBUG: print('ADDING    :,', end = '')

for line in f:
    line = line.rstrip('\n')
    linenum += 1
    match = re.search(SECTION_RECORD_PATTERN, line)
    if match:
        if DEBUG: print('ORIGINAL  : (' + str(linenum) + ') "' + line + '"')
        temp_entry = [ match.group(1).strip(), match.group(2).strip(), match.group(3).strip(), match.group(4).strip(), match.group(5).strip(), match.group(6).strip(), match.group(7).strip() ]
        if DEBUG: print('FOUND     : "' + temp_entry[0] + '"|"' + temp_entry[1] + '"|"' + temp_entry[2] + '"|"' + temp_entry[3] + '"|"' + temp_entry[4] + '"|"' + temp_entry[5] + '"|"' + temp_entry[6] + '"')
        for i in range(len(temp_entry)):
            if temp_entry[i][0:1] == '(':
                temp_entry[i] = ' ' + temp_entry[i]

        if temp_entry[0] == "":
            found_list[-1] = list(map(lambda s1, s2: s1 + s2, found_list[-1], temp_entry))
            if DEBUG: print('MODIFYING :', end = '')
            if DEBUG: print('"' + found_list[-1][0] + '","' + found_list[-1][1] + '","' + found_list[-1][2] + '","' + found_list[-1][3] + '","' + found_list[-1][4] + '","' + found_list[-1][5] + '","' + found_list[-1][6] + '"')
        else:
            list_entry = temp_entry
            if DEBUG: print('ADDING    :,', end = '')
            if DEBUG: print('"' + list_entry[0] + '","' + list_entry[1] + '","' + list_entry[2] + '","' + list_entry[3] + '","' + list_entry[4] + '","' + list_entry[5] + '","' + list_entry[6] + '"')
            found_list.append(list_entry)


    if re.search(SECTION_BEGIN_OR_END_PATTERN, line):
        break

f.close

for i in found_list:
    match = re.search(r'(.*)(?: )\((.*)\)', i[2])
    if match:
        i[2] = match.group(1)
        i.insert(3, match.group(2))

    if i[4][0:2] == '0x':
        size_dec = str(int(i[4],16))
    else:
        size_dec = ''
    i.insert(5, size_dec)

    if i[6][0:2] == '0x':
        space_addr_dec = str(int(i[6],16))
    else:
        space_addr_dec = ''
    i.insert(7, space_addr_dec)

    if i[8][0:2] == '0x':
        chip_addr_dec = str(int(i[8],16))
    else:
        chip_addr_dec = ''
    i.insert(9, chip_addr_dec)


if OPTION_USE_OWN_DATA_STRUCTURE:
    if OPTION_USE_OUTPUT_FILE:
        with open(OUT_FILENAME + '.' + OUT_FILEEXT, 'w') as f:
            if OPTION_OUTPUT_FORMAT_SQL:
                f.write('PRAGMA foreign_keys = off;\n')
                f.write('BEGIN TRANSACTION;\n')
                f.write('CREATE TABLE IF NOT EXISTS locate_result (Chip, Group_name, Section, Section_ID, Size_MAU_HEX, Size_DEC INT, Space_addr_HEX, Space_addr_DEC INT, Chip_addr_HEX, Chip_addr_DEC INT, Alignment TEXT);' + '\n')
                for i in found_list:
                    f.write('INSERT INTO locate_result (Chip, Group_name, Section, Section_ID, Size_MAU_HEX, Size_DEC, Space_addr_HEX, Space_addr_DEC, Chip_addr_HEX, Chip_addr_DEC, Alignment) VALUES (')
                    f.write('"' + i[0] + '", "' + i[1] + '", "' + i[2] + '", "' + i[3] + '", "' + i[4] + '", "' + i[5] + '", "' + i[6] + '", "' + i[7] + '", "' + i[8] + '", "' + i[9] + '", "' + i[10] + '"' + ');' + '\n')
                f.write('COMMIT TRANSACTION;\n')
            else:
                f.write('"Chip","Group_name","Section","Section_ID","Size_MAU_HEX","Size_DEC","Space_addr_HEX","Space_addr_DEC","Chip_addr_HEX","Chip_addr_DEC","Alignment"' + '\n')
                for i in found_list:
                    f.write('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '","' + i[10] + '"' + '\n')
    else:
        if OPTION_OUTPUT_FORMAT_SQL:
            print('PRAGMA foreign_keys = off;')
            print('BEGIN TRANSACTION;')
            print('CREATE TABLE IF NOT EXISTS locate_result (Chip, Group_name, Section, Section_ID, Size_MAU_HEX, Size_DEC INT, Space_addr_HEX, Space_addr_DEC INT, Chip_addr_HEX, Chip_addr_DEC INT, Alignment TEXT);')
            for i in found_list:
                print('INSERT INTO locate_result (Chip, Group_name, Section, Section_ID, Size_MAU_HEX, Size_DEC, Space_addr_HEX, Space_addr_DEC, Chip_addr_HEX, Chip_addr_DEC, Alignment) VALUES (', end = '')
                print('"' + i[0] + '", "' + i[1] + '", "' + i[2] + '", "' + i[3] + '", "' + i[4] + '", "' + i[5] + '", "' + i[6] + '", "' + i[7] + '", "' + i[8] + '", "' + i[9] + '", "' + i[10] + '"' + ');')
            print('COMMIT TRANSACTION;')
        else:
            print('"Chip","Group_name","Section","Section_ID","Size_MAU_HEX","Size_DEC","Space_addr_HEX","Space_addr_DEC","Chip_addr_HEX","Chip_addr_DEC","Alignment"')
            for i in found_list:
                print('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '","' + i[10] + '"')
else:
    print('Set "OPTION_USE_OWN_DATA_STRUCTURE = False" to get data')
    '''
    if OPTION_USE_OUTPUT_FILE:
        with open(OUT_FILENAME + '.' + OUT_FILEEXT, 'w') as f:
            if OPTION_OUTPUT_FORMAT_SQL:
                f.write('PRAGMA foreign_keys = off;\n')
                f.write('BEGIN TRANSACTION;\n')
                f.write('"Chip","Group_name","Section","Section_ID","Size_MAU_HEX","Size_DEC","Space_addr_HEX","Space_addr_DEC","Chip_addr_HEX","Chip_addr_DEC","Alignment"\n')
                for i in found_list:
                    f.write('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '","' + i[10] + '"' + '\n')
                f.write('COMMIT TRANSACTION;\n')
            else:
                f.write('"Chip","Group_name","Section","Section_ID","Size_MAU_HEX","Size_DEC","Space_addr_HEX","Space_addr_DEC","Chip_addr_HEX","Chip_addr_DEC","Alignment"\n')
                for i in found_list:
                    f.write('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '","' + i[10] + '"' + '\n')
    else:
        if OPTION_OUTPUT_FORMAT_SQL:
            print('PRAGMA foreign_keys = off;')
            print('BEGIN TRANSACTION;')
            print('"Chip","Group_name","Section","Section_ID","Size_MAU_HEX","Size_DEC","Space_addr_HEX","Space_addr_DEC","Chip_addr_HEX","Chip_addr_DEC","Alignment"')
            for i in found_list:
                print('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '","' + i[10] + '"')
            print('COMMIT TRANSACTION;\n')
        else:
            print('"Chip","Group_name","Section","Section_ID","Size_MAU_HEX","Size_DEC","Space_addr_HEX","Space_addr_DEC","Chip_addr_HEX","Chip_addr_DEC","Alignment"')
            for i in found_list:
                print('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '","' + i[10] + '"')
    '''

#locate_result (Chip, Group_name, Section, Section_ID, Size_MAU_HEX, Size_DEC, Space_addr_HEX, Space_addr_DEC, Chip_addr_HEX, Chip_addr_DEC TEXT, Alignment TEXT);
